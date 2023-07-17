#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int
main(int argc, char* argv[])
{
  // Future output of async is bound to a reference, the destructor won't
  // block until the lambda function finishes.
  auto t1 = std::async(std::launch::async, [] {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread 1"
              << "\n";
  });

  auto t2 = std::async(std::launch::async, [] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread 2"
              << "\n";
  });

  std::async(std::launch::async, [] {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread 3"
              << "\n";
  });

  std::async(std::launch::async, [] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread 4"
              << "\n";
  });

  return EXIT_SUCCESS;
}