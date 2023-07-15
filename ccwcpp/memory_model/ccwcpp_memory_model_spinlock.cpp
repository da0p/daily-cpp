#include <atomic>
#include <thread>

class Spinlock
{
private:
  std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
  void lock()
  {
    while(flag.test_and_set())
      ;
  }

  void unlock() { flag.clear(); }
};

Spinlock spin;

void
workOnResource()
{
  spin.lock();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  spin.unlock();
}

int
main(int argc, char* argv[])
{
  std::thread t1(workOnResource);
  std::thread t2(workOnResource);

  t1.join();
  t2.join();

  return EXIT_SUCCESS;
}