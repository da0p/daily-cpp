#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

constexpr auto tenMill = 10000000;

// Double-checked locking pattern
class MySingleton
{
public:
  static MySingleton* getInstance()
  {
    //
    MySingleton* sin = instance.load();
    if(!sin) {
      std::lock_guard<std::mutex> myLock(myMutex);
      // another thread could kick in between check sin and lock, therefore
      // another load is needed
      sin = instance.load(std::memory_order_relaxed);
      if(!sin) {
        // This will surely happen before store during sequential consistency
        sin = new MySingleton();

        // store with sequential consistency
        instance.store(sin);
      }
    }
    int volatile dummy{};
    return sin;
  }

private:
  MySingleton() = default;
  ~MySingleton() = default;
  MySingleton(MySingleton const&) = delete;
  MySingleton& operator=(MySingleton const&) = delete;

  static std::atomic<MySingleton*> instance;
  static std::mutex myMutex;
};

std::atomic<MySingleton*> MySingleton::instance;
std::mutex MySingleton::myMutex;

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