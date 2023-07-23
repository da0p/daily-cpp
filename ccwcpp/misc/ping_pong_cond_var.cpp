#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <thread>

bool dataReady{false};

std::mutex mutex_;
std::condition_variable condVar1;
std::condition_variable condVar2;

std::atomic<int> counter{};
constexpr int countLimit = 1'000'000;

void
ping()
{
  while(counter <= countLimit) {
    {
      std::unique_lock<std::mutex> lck(mutex_);
      // ping thread will wait for the notification of condVar1 variable and
      // sends its notification with condVar2.
      // dataReady protects against spurious and lost wakeups.
      condVar1.wait(lck, [] { return dataReady == false; });
      dataReady = true;
    }
    ++counter;
    condVar2.notify_one();
  }
}

void
pong()
{
  while(counter <= countLimit) {
    {
      std::unique_lock<std::mutex> lck(mutex_);
      condVar2.wait(lck, [] { return dataReady == true; });
      dataReady = false;
    }
    condVar1.notify_one();
  }
}

int
main(int argc, char* argv[])
{
  auto start = std::chrono::system_clock::now();

  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();

  std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
  std::cout << "Duration: " << dur.count() << " seconds"
            << "\n";

  return EXIT_SUCCESS;
}