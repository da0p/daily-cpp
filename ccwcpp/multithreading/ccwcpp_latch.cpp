#include <iostream>
#include <latch>
#include <mutex>
#include <thread>

std::latch workDone(6);
std::mutex coutMutex;

void
synchronizedOut(std::string const& msg)
{
  std::lock_guard<std::mutex> lo(coutMutex);
  std::cout << msg;
}

class Worker
{
public:
  Worker(std::string n)
    : name(n){};

  void operator()()
  {
    synchronizedOut(name + ": " + "Work done!\n");
    // wait until latch counter becomes zero
    workDone.arrive_and_wait();
    synchronizedOut(name + ": " + "See you tomorrow!\n");
  }

private:
  std::string name;
};

int
main(int argc, char* argv[])
{
  Worker herb("Herb");
  std::thread herbWork(herb);

  Worker scott("Scott");
  std::thread scottWork(scott);

  Worker bjarne("Bjarne");
  std::thread bjaneWork(bjarne);

  Worker andrei("Andrei");
  std::thread andreiWork(andrei);

  Worker andrew("Andrew");
  std::thread andrewWork(andrew);

  Worker david("David");
  std::thread davidWork(david);

  herbWork.join();
  scottWork.join();
  bjaneWork.join();
  andreiWork.join();
  andrewWork.join();
  davidWork.join();
}