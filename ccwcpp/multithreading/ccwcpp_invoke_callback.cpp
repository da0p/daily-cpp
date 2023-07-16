#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ratio>
#include <thread>
#include <vector>

int
main(int argc, char* argv[])
{
  auto func = [](std::stop_token stoken) {
    int counter{0};
    auto thread_id = std::this_thread::get_id();
    std::stop_callback callback(stoken, [&counter, thread_id] {
      std::cout << "Thread id: " << thread_id << "; counter: " << counter
                << "\n";
    });
    while(counter < 10) {
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      ++counter;
    }
  };

  std::vector<std::jthread> vecThreads{10};
  for(auto& thr : vecThreads) {
    thr = std::jthread(func);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  for(auto& thr : vecThreads) {
    thr.request_stop();
  }

  // Let the thread sleep before registering the callback to simulate that
  // the stop request arrives before registering the callback.
  auto func2 = [](std::stop_token stoken) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for(int i = 0; i < 10; i++) {
      std::stop_callback callback(stoken, [i] { std::cout << i << " "; });
    }
    std::cout << "\n";
  };

  std::jthread thr1 = std::jthread(func2);
  std::jthread thr2 = std::jthread(func2);
  thr1.request_stop();
  thr2.request_stop();

  return EXIT_SUCCESS;
}