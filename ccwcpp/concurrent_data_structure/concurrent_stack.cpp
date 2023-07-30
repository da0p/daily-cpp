#include <cstdlib>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <stack>
#include <stdexcept>
#include <utility>

template<typename T, template<typename, typename> class Cont = std::deque>
class ConcurrentStack
{
public:
  ConcurrentStack() = default;
  ConcurrentStack(ConcurrentStack const&) = delete;
  ConcurrentStack& operator=(ConcurrentStack const&) = delete;
  void push(T val)
  {
    std::lock_guard<std::mutex> lockStack(mMutexStack);
    mMyStack.push(std::move(val));
  }
  T topAndPop()
  {
    std::lock_guard<std::mutex> lockStack(mMutexStack);
    if(mMyStack.empty()) {
      throw std::out_of_range("The stack is empty!");
    }
    auto val = mMyStack.top();
    mMyStack.pop();
    return val;
  }

private:
  mutable std::mutex mMutexStack;
  std::stack<T, Cont<T, std::allocator<T>>> mMyStack;
};

int
main(int argc, char* argv[])
{
  ConcurrentStack<int> conStack;

  auto fut_1 = std::async([&conStack] { conStack.push(2011); });
  auto fut_2 = std::async([&conStack] { conStack.push(2014); });
  auto fut_3 = std::async([&conStack] { conStack.push(2017); });
  auto fut_4 = std::async([&conStack] { return conStack.topAndPop(); });
  auto fut_5 = std::async([&conStack] { return conStack.topAndPop(); });
  auto fut_6 = std::async([&conStack] { return conStack.topAndPop(); });

  fut_1.get();
  fut_2.get();
  fut_3.get();

  std::cout << fut_4.get() << "\n";
  std::cout << fut_5.get() << "\n";
  std::cout << fut_6.get() << "\n";

  return EXIT_SUCCESS;
}