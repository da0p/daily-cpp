#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <thread>

std::atomic_flag condAtomicFlag1{};
std::atomic_flag condAtomicFlag2{};
std::atomic<int> counter{};
constexpr int countLimit = 1'000'000;

void
ping()
{
  while(counter <= countLimit) {
    condAtomicFlag1.wait(false);
    condAtomicFlag1.clear();

    ++counter;

    condAtomicFlag2.test_and_set();
    condAtomicFlag2.notify_one();
  }
}

void
pong()
{
  while(counter <= countLimit) {
    condAtomicFlag2.wait(false);
    condAtomicFlag2.clear();

    condAtomicFlag1.test_and_set();
    condAtomicFlag1.notify_one();
  }
}

int
main(int argc, char* argv[])
{
  auto start = std::chrono::system_clock::now();

  condAtomicFlag1.test_and_set();
  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();

  std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
  std::cout << "Duration: " << dur.count() << " seconds"
            << "\n";

  return EXIT_SUCCESS;
}