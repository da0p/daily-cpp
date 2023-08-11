#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <ratio>
#include <thread>

std::mutex mut;
std::condition_variable_any condVar;
bool dataReady{false};

void
doTheWork()
{
  std::cout << "Processing shared data."
            << "\n";
}

void
waitingForWork()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << "Worker: Waiting for work."
            << "\n";
  std::unique_lock<std::mutex> lck(mut);
  condVar.wait(lck, [] { return dataReady; });
  doTheWork();
  std::cout << "Work done."
            << "\n";
}

void
setDataReady()
{
  {
    std::lock_guard<std::mutex> lck(mut);
    dataReady = false;
  }
  std::cout << "Sender: Data is ready"
            << "\n";
  condVar.notify_one();
}

int
main(int argc, char* argv[])
{
  std::thread t1(waitingForWork);
  std::thread t2(setDataReady);

  t1.join();
  t2.join();
}