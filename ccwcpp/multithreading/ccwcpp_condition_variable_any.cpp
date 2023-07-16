#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <ratio>
#include <thread>

std::mutex mut;
std::condition_variable_any condVar;
bool dataReady;

void
receiver(std::stop_token stopToken)
{
  std::cout << "Waiting"
            << "\n";

  std::unique_lock<std::mutex> lck(mut);
  bool ret = condVar.wait(lck, stopToken, [] { return dataReady; });
  if(ret) {
    std::cout << "Notification received: "
              << "\n";
  } else {
    std::cout << "Stop request received"
              << "\n";
  }
}

void
sender()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  {
    std::lock_guard<std::mutex> lck(mut);
    dataReady = true;
    std::cout << "Send notification"
              << "\n";
  }
  condVar.notify_one();
}

int
main(int argc, char* argv[])
{
  std::jthread t1(receiver);
  std::jthread t2(sender);

  t1.request_stop();

  t1.join();
  t2.join();
}