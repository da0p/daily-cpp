#include <atomic>
#include <chrono>
#include <coroutine>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

class Event
{
public:
  Event() = default;

  Event(Event const&) = delete;
  Event(Event&&) = delete;
  Event& operator=(Event const&) = delete;
  Event& operator=(Event&&) = delete;

  class Awaiter;
  Awaiter operator co_await() const noexcept;

  void notify() noexcept;

private:
  friend class Awaiter;
  mutable std::atomic<void*> suspendedWaiter{nullptr};
  mutable std::atomic<bool> notified{false};
};

class Event ::Awaiter
{
public:
  Awaiter(Event const& eve)
    : event(eve)
  {
  }
  bool await_ready() const;
  bool await_suspend(std::coroutine_handle<> coHandle);
  void await_resume() noexcept {}

private:
  friend class Event;
  Event const& event;
  std::coroutine_handle<> coroutineHandle;
};

bool
Event::Awaiter::await_ready() const
{
  std::cout << "\nawait_ready..."
            << "\n";
  // allow at most one waiter
  if(event.suspendedWaiter.load() != nullptr) {
    throw std::runtime_error("More than one waiter is not valid");
  }

  // if it's false, it causes suspenseion of the coroutine.
  return event.notified;
}

bool
Event::Awaiter::await_suspend(std::coroutine_handle<> coHandle)
{
  std::cout << "\nawait_suspend...\n";

  // Stores the coroutine handle for later invocation.
  coroutineHandle = coHandle;

  Event const& ev = event;
  ev.suspendedWaiter.store(this);

  if(ev.notified) {
    void* thisPtr = this;

    if(ev.suspendedWaiter.compare_exchange_strong(thisPtr, nullptr)) {
      return false;
    }
  }
  return true;
}

void
Event::notify() noexcept
{
  notified = true;
  void* waiter = suspendedWaiter.load();

  if(waiter != nullptr && suspendedWaiter.compare_exchange_strong(waiter, nullptr)) {
    // stored coroutineHandle is used to resume
    static_cast<Awaiter*>(waiter)->coroutineHandle.resume();
  }
}

Event::Awaiter Event::operator co_await() const noexcept
{
  return Awaiter{*this};
}

struct Task
{
  struct promise_type
  {
    Task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

Task
receiver(Event& event)
{
  auto start = std::chrono::high_resolution_clock::now();
  co_await event;

  std::cout << "Got the notification! "
            << "\n";
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Waited " << elapsed.count() << " seconds."
            << "\n";
}

int
main(int argc, char* argv[])
{
  std::cout << "Notification before waiting"
            << "\n";
  Event event1{};

  auto senderThread1 = std::thread([&event1] { event1.notify(); });

  auto receiverThread1 = std::thread(receiver, std::ref(event1));

  receiverThread1.join();
  senderThread1.join();

  std::cout << "\n\n";
  std::cout << "Notification after 2 seconds waiting"
            << "\n\n";

  Event event2{};
  auto receiverThread2 = std::thread(receiver, std::ref(event2));
  auto senderThread2 = std::thread([&event2] {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    event2.notify();
  });
  receiverThread2.join();
  senderThread2.join();
}