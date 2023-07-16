#include <future>
#include <iostream>
#include <thread>

void
func1(std::stop_token stopToken, std::string const& msg)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  if(stopToken.stop_requested()) {
    std::cout << msg << ": Stop requested\n";
  }
}

void
func2(
  std::promise<void> promise,
  std::stop_token stopToken,
  std::string const& msg
)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::stop_callback callback(stopToken, [&msg] {
    std::cout << msg << ": Stop requested\n";
  });
}

int
main(int argc, char* argv[])
{
  std::stop_source stopSource;
  std::stop_token stopToken = std::stop_token(stopSource.get_token());

  std::thread thr1 = std::thread(func1, stopToken, "std::thread");

  std::jthread jthr = std::jthread(func1, stopToken, "std::jthread");

  auto fut1 = std::async([stopToken] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(stopToken.stop_requested()) {
      std::cout << "std::async: Stop requested\n";
    }
  });

  std::promise<void> prom;
  auto fut2 = prom.get_future();

  std::thread thr2(func2, std::move(prom), stopToken, "std::promise");

  // If joining threads before sending stop request, it will be too late.
  // thr1.join();
  // thr2.join();
  stopSource.request_stop();
  if(stopToken.stop_requested()) {
    std::cout << "main: Stop requested\n";
  }

  thr1.join();
  thr2.join();
}