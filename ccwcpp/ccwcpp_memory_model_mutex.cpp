#include <mutex>
#include <thread>

std::mutex mut;

void
workOnResource()
{
  mut.lock();
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  mut.unlock();
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