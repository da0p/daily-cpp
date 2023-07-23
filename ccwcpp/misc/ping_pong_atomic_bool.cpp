#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <thread>

std::atomic<bool> atomicBool{};
std::atomic<int> counter{};
constexpr int countLimit = 1'000'000;

void
ping()
{
  while(counter <= countLimit) {
    atomicBool.wait(true);
    atomicBool.store(true);

    ++counter;

    atomicBool.notify_one();
  }
}

void
pong()
{
  while(counter <= countLimit) {
    atomicBool.wait(false);
    atomicBool.store(false);
    atomicBool.notify_one();
  }
}

int
main(int argc, char* argv[])
{
  auto start = std::chrono::system_clock::now();

  atomicBool.store(true);
  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();

  std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
  std::cout << "Duration: " << dur.count() << " seconds"
            << "\n";

  return EXIT_SUCCESS;
}