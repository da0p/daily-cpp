#include <cstdlib>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

std::mutex coutMutex;

struct Div
{
  void operator()(std::promise<int>&& intPromise, int a, int b)
  {
    intPromise.set_value(a / b);
  }
};

struct Requestor
{
  void operator()(std::shared_future<int> sharedFut)
  {
    // lock std::cout
    std::lock_guard<std::mutex> coutGuard(coutMutex);

    // get the thread id
    std::cout << "threadId(" << std::this_thread::get_id() << "): ";

    std::cout << "20 / 10 = " << sharedFut.get() << "\n";
  }
};

int
main(int argc, char* argv[])
{

  // define the promises
  std::promise<int> divPromise;

  // get the futures
  std::shared_future<int> divResult = divPromise.get_future();
  // then it can be
  // std::shared_future<int> sharedResult = divResult.share();

  // calculate the result in a separate thread
  Div div;
  std::thread divThread(div, std::move(divPromise), 20, 10);

  Requestor req;
  // std::shared_future can be copied, not like std::future, which can only
  // be movable, not copyable.
  std::thread sharedThread1(req, divResult);
  std::thread sharedThread2(req, divResult);
  std::thread sharedThread3(req, divResult);
  std::thread sharedThread4(req, divResult);
  std::thread sharedThread5(req, divResult);

  divThread.join();

  sharedThread1.join();
  sharedThread2.join();
  sharedThread3.join();
  sharedThread4.join();
  sharedThread5.join();

  return EXIT_SUCCESS;
}