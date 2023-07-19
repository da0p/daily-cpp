#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex coutMutex;

class Worker
{
public:
  Worker(std::string n)
    : name(n){};

  void operator()()
  {
    for(int i = 1; i <= 3; ++i) {
      // begin work
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      // end work
      std::lock_guard<std::mutex> coutLock(coutMutex);
      std::cout << name << ": "
                << "Work " << i << " done !!!\n";
    } // where destructor of lock_guard occurs and releases the mutex
  }

private:
  std::string name;
};

int
main(int argc, char* argv[])
{
  std::cout << "Boss: Let's start working."
            << "\n\n";

  std::thread herb = std::thread(Worker("Herb"));
  std::thread andrei = std::thread(Worker("Andrei"));
  std::thread scott = std::thread(Worker("Scott"));
  std::thread bjarne = std::thread(Worker("Bjarne"));
  std::thread bart = std::thread(Worker("Bart"));
  std::thread jenne = std::thread(Worker("Jenne"));

  herb.join();
  andrei.join();
  scott.join();
  bjarne.join();
  bart.join();
  jenne.join();

  std::cout << "\n"
            << "Boss: Let's go home."
            << "\n";

  return EXIT_SUCCESS;
}