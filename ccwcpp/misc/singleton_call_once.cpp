#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

constexpr auto tenMill = 10000000;

class MySingleton
{
public:
  static MySingleton& getInstance()
  {
    std::call_once(initInstanceFlag, &MySingleton::initSingleton);
    int volatile dummy{};
    return *instance;
  }

private:
  MySingleton() = default;
  ~MySingleton() = default;
  MySingleton(MySingleton const&) = delete;
  MySingleton& operator=(MySingleton const&) = delete;

  static MySingleton* instance;
  static std::once_flag initInstanceFlag;

  static void initSingleton() { instance = new MySingleton; }
};

MySingleton* MySingleton::instance = nullptr;
std::once_flag MySingleton::initInstanceFlag;

std::chrono::duration<double>
getTime()
{
  auto begin = std::chrono::system_clock::now();
  for(size_t i = 0; i <= tenMill; ++i) {
    MySingleton::getInstance();
  }
  return std::chrono::system_clock::now() - begin;
}

int
main(int argc, char* argv[])
{
  auto fut_1 = std::async(std::launch::async, getTime);
  auto fut_2 = std::async(std::launch::async, getTime);
  auto fut_3 = std::async(std::launch::async, getTime);
  auto fut_4 = std::async(std::launch::async, getTime);

  auto const total = fut_1.get() + fut_2.get() + fut_3.get() + fut_4.get();

  std::cout << total.count() << "\n";
}