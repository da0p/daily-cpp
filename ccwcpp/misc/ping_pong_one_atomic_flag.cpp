#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <thread>

std::atomic_flag condAtomicFlag{};
std::atomic<int> counter{};
constexpr int countLimit = 1'000'000;

void
ping()
{
  while(counter <= countLimit) {
    condAtomicFlag.wait(true);
    condAtomicFlag.test_and_set();

    ++counter;

    condAtomicFlag.notify_one();
  }
}

void
pong()
{
  while(counter <= countLimit) {
    condAtomicFlag.wait(false);
    condAtomicFlag.clear();
    condAtomicFlag.notify_one();
  }
}

int
main(int argc, char* argv[])
{
  auto start = std::chrono::system_clock::now();

  condAtomicFlag.test_and_set();
  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();

  std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
  std::cout << "Duration: " << dur.count() << " seconds"
            << "\n";

  return EXIT_SUCCESS;
}