#include <chrono>
#include <future>
#include <iostream>

constexpr auto tenMill = 10000000;

class MySingleton
{
public:
  static MySingleton& getInstance()
  {
    static MySingleton instance;
    // to not let compiler to optimize in order to measure time
    int volatile dumy{};
    return instance;
  }

private:
  MySingleton() = default;
  ~MySingleton() = default;
  MySingleton(MySingleton const&) = delete;
  MySingleton& operator=(MySingleton const&) = delete;
};

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