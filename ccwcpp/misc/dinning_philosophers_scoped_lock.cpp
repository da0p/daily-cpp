#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

int
my_rand(int min, int max)
{
  static std::mt19937 rnd(std::time(nullptr));
  return std::uniform_int_distribution<>(min, max)(rnd);
}

std::mutex mo;

void
phil(int ph, std::mutex& ma, std::mutex& mb)
{
  while(true) {
    int duration = my_rand(1000, 2000);
    {
      std::lock_guard<std::mutex> g(mo);
      std::cout << ph << " thinks " << duration << "ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::scoped_lock scop(ma, mb);

    {
      std::lock_guard<std::mutex> g(mo);
      std::cout << "\t\t" << ph << " got ma, mb\n";
    }

    duration = my_rand(1000, 2000);
    {
      std::lock_guard<std::mutex> g(mo);
      std::cout << "\t\t\t\t" << ph << " eats " << duration << "ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
  }
}

int
main(int argc, char* argv[])
{
  std::mutex m1, m2, m3, m4;

  std::thread t1([&] { phil(1, m1, m2); });
  std::thread t2([&] { phil(2, m2, m3); });
  std::thread t3([&] { phil(3, m3, m4); });
  std::thread t4([&] { phil(4, m1, m4); });

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}