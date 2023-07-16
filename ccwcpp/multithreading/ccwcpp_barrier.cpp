#include <barrier>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::barrier workDone{6};
std::mutex coutMutex;

void
synchronizedOut(std::string const& msg) noexcept
{
  std::lock_guard<std::mutex> lo(coutMutex);
  std::cout << msg;
}

class FullTimeWorker
{
public:
  FullTimeWorker(std::string n)
    : name(n){};

  void operator()()
  {
    synchronizedOut(name + ": " + "Morning work done!\n");
    workDone.arrive_and_wait();
    // after 0 is reached, barrier value will be reset, but because other
    // partime workers reduce the initial value, after all, here the value will
    // be 3.
    synchronizedOut(name + ": " + "Afternoon work done!\n");
    workDone.arrive_and_wait();
  }

private:
  std::string name;
};

class PartTimeWorker
{
public:
  PartTimeWorker(std::string n)
    : name(n){};

  void operator()()
  {
    synchronizedOut(name + ": " + "Morning work done!\n");
    // reduce the initial value
    workDone.arrive_and_drop();
  }

private:
  std::string name;
};

int
main(int argc, char* argv[])
{
  FullTimeWorker herb("Herb");
  std::thread herbWork(herb);

  FullTimeWorker scott("Scott");
  std::thread scottWork(scott);

  FullTimeWorker bjarne("Bjarne");
  std::thread bjarneWork(bjarne);

  PartTimeWorker andrei("Andrei");
  std::thread andreiWork(andrei);

  PartTimeWorker andrew("Andrew");
  std::thread andrewWork(andrew);

  PartTimeWorker david("David");
  std::thread davidWork(david);

  herbWork.join();
  scottWork.join();
  bjarneWork.join();
  andreiWork.join();
  andrewWork.join();
  davidWork.join();

  return EXIT_SUCCESS;
}