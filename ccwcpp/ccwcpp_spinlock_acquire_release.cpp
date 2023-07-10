#include <atomic>
#include <cstdlib>
#include <iostream>
#include <thread>

class Spinlock
{
private:
  std::atomic_flag flag;

public:
  Spinlock()
    : flag(ATOMIC_FLAG_INIT)
  {
  }

  void lock()
  {
    while(flag.test_and_set(std::memory_order_acquire))
      ;
  }

  void unlock() { flag.clear(std::memory_order_release); }
};

Spinlock spin;

void
workOnResource()
{
  spin.lock();
  // shared resource
  std::cout << "I'm a shared resource!\n";

  spin.unlock();
}

int
main()
{

  std::thread t1(workOnResource);
  std::thread t2(workOnResource);

  t1.join();
  t2.join();

  return EXIT_SUCCESS;
}