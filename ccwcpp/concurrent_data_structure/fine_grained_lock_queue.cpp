#include <condition_variable>
#include <cstdlib>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <utility>

template<typename T>
class ConcurrentQueue
{
private:
  struct Node
  {
    T data;
    std::unique_ptr<Node> next;
    Node(T d)
      : data(std::move(d))
    {
    }
  };
  std::unique_ptr<Node> mHead;
  Node* mTail;
  std::mutex mHeadMutex;
  std::mutex mTailMutex;
  std::condition_variable waitForValue;

public:
  ConcurrentQueue()
    : mHead(new Node(T{}))
    , mTail(mHead.get()){};
  std::unique_ptr<T> pop()
  {
    std::lock_guard<std::mutex> headLock(mHeadMutex);
    {
      std::unique_lock<std::mutex> tailLock(mTailMutex);
      waitForValue.wait(tailLock, [this] { return mHead.get() != mTail; });
    }
    std::unique_ptr<T> result = std::make_unique<T>(std::move(mHead->data));
    std::unique_ptr<Node> oldHead = std::move(mHead);
    mHead = std::move(oldHead->next);
    if(!mHead) {
      mTail = nullptr;
    }

    return result;
  }
  void push(T val)
  {
    std::unique_ptr<Node> dummyNode = std::make_unique<Node>(Node(T{}));
    Node* newTail = dummyNode.get();
    {
      std::unique_lock<std::mutex> tailLock(mTailMutex);
      mTail->next = std::move(dummyNode);
      mTail->data = val;
      mTail = newTail;
    }
    waitForValue.notify_one();
  }
  ConcurrentQueue(ConcurrentQueue const& other) = delete;
  ConcurrentQueue& operator=(ConcurrentQueue const& other) = delete;
};

int
main(int argc, char* argv[])
{
  ConcurrentQueue<int> conQueue;

  auto fut_1 = std::async([&conQueue] { conQueue.push(2011); });
  auto fut_2 = std::async([&conQueue] { conQueue.push(2014); });
  auto fut_3 = std::async([&conQueue] { conQueue.push(2017); });

  auto fut_4 = std::async([&conQueue] { return *conQueue.pop(); });
  auto fut_5 = std::async([&conQueue] { return *conQueue.pop(); });
  auto fut_6 = std::async([&conQueue] { return *conQueue.pop(); });

  fut_1.get();
  fut_2.get();
  fut_3.get();

  std::cout << fut_4.get() << "\n";
  std::cout << fut_5.get() << "\n";
  std::cout << fut_6.get() << "\n";

  return EXIT_SUCCESS;
}
