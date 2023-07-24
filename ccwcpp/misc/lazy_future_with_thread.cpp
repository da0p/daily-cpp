#include <coroutine>
#include <iostream>
#include <memory>
#include <thread>

template<typename T>
struct MyFuture
{
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  handle_type coro;

  MyFuture(handle_type h)
    : coro(h)
  {
  }
  ~MyFuture()
  {
    if(coro) {
      coro.destroy();
    }
  }
  T get()
  {
    std::cout << "MyFuture::get: "
              << "std::this_thread::get_id(): " << std::this_thread::get_id()
              << "\n\n";

    // resume the coroutine in another thread
    // It's important here that the promise, resumed in a separate thread,
    // finishes before it returns coro.promise().result.
    // Otherwise, we will get arbitrary value.
    // we cannot use jthread here because jthread will join when it goes out
    // of scope, and here it's too late, we will get the result before jthread
    // goes out of scope.
    std::thread t([this] { coro.resume(); });
    t.join();
    // if we want to use jthread, then we can create a scope around jthread
    // {
    //      std::jthread t([this]{coro.resume():});
    // }
    // return coro.promise().result;
    //
    // or we can create a temporary jthread, since it will go out of scope
    // immediately.
    // std::jthread([this]{coro.resume();});
    // return coro.promise().result;
    //
    //
    return coro.promise().result;
  }

  struct promise_type
  {
    promise_type()
    {
      std::cout << "promise_type::promise_type: "
                << "std::this_thread::get_id(): " << std::this_thread::get_id()
                << "\n\n";
    }
    ~promise_type()
    {
      std::cout << "promise_type::~promise_type: "
                << "std::this_thread::get_id(): " << std::this_thread::get_id()
                << "\n\n";
    }
    T result;
    auto get_return_object()
    {
      return MyFuture{handle_type::from_promise(*this)};
    }
    void return_value(T v)
    {
      std::cout << "promise_type::return_vlaue: "
                << "std::this_thread::get_id(): " << std::this_thread::get_id()
                << "\n\n";

      std::cout << v << "\n";
      result = v;
    }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept
    {
      std::cout << "promise_type::final_suspend: "
                << "std::this_thread::get_id(): " << std::this_thread::get_id()
                << "\n\n";
      return {};
    }
    void unhandled_exception() { std::exit(1); }
  };
};

MyFuture<int>
createFuture()
{
  co_return 2021;
}

int
main(int argc, char* argv[])
{
  std::cout << "main: "
            << "std::this_thread::get_id(): " << std::this_thread::get_id()
            << "\n\n";
  auto fut = createFuture();
  auto res = fut.get();
  std::cout << "res: " << res << "\n";
}