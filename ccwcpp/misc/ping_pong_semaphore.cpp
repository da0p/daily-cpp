#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <semaphore>
#include <thread>

std::counting_semaphore<1> signal2Ping(0);
std::counting_semaphore<1> signal2Pong(0);
std::atomic<int> counter{};
constexpr int countLimit = 1'000'000;

void
ping()
{
  while(counter <= countLimit) {
    signal2Ping.acquire();
    ++counter;
    signal2Pong.release();
  }
}

void
pong()
{
  while(counter <= countLimit) {
    signal2Pong.acquire();
    signal2Ping.release();
  }
}

int
main(int argc, char* argv[])
{
  auto start = std::chrono::system_clock::now();

  signal2Ping.release();
  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();

  std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
  std::cout << "Duration: " << dur.count() << " seconds"
            << "\n";

  return EXIT_SUCCESS;
}