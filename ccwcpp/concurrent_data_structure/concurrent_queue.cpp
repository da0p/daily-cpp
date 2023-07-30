#include <future>
#include <iostream>
#include <limits>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>

template<typename T, template<typename, typename> class Cont = std::deque>
class ConcurrentQueue
{
public:
  void push(T val)
  {
    std::lock_guard<std::mutex> lockQueue(mMutexQueue);
    mMyQueue.push(std::move(val));
  }
  T frontAndPop()
  {
    std::lock_guard<std::mutex> lockQueue(mMutexQueue);
    if(mMyQueue.empty()) {
      throw std::out_of_range("The queue is empty");
    }
    auto val = mMyQueue.front();
    mMyQueue.pop();
    return val;
  }
  ConcurrentQueue() = default;
  ConcurrentQueue(ConcurrentQueue const&) = delete;
  ConcurrentQueue& operator=(ConcurrentQueue const&) = delete;

private:
  mutable std::mutex mMutexQueue;
  std::queue<T, Cont<T, std::allocator<T>>> mMyQueue;
};

int
main(int argc, char* argv[])
{
  ConcurrentQueue<int> conQueue;
  auto fut_1 = std::async([&conQueue] { conQueue.push(2011); });
  auto fut_2 = std::async([&conQueue] { conQueue.push(2014); });
  auto fut_3 = std::async([&conQueue] { conQueue.push(2017); });
  auto fut_4 = std::async([&conQueue] { return conQueue.frontAndPop(); });
  auto fut_5 = std::async([&conQueue] { return conQueue.frontAndPop(); });
  auto fut_6 = std::async([&conQueue] { return conQueue.frontAndPop(); });

  fut_1.get();
  fut_2.get();
  fut_3.get();

  std::cout << fut_4.get() << "\n";
  std::cout << fut_5.get() << "\n";
  std::cout << fut_6.get() << "\n";

  return EXIT_SUCCESS;
}