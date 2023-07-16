#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

struct CriticalData
{
  std::mutex mut;
};

void
deadlock(CriticalData& a, CriticalData& b)
{
  std::cout << "Thread: " << std::this_thread::get_id() << " first mutex"
            << "\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::cout << "Thread: " << std::this_thread::get_id() << " second mutex"
            << "\n";

  std::cout << "Thread: " << std::this_thread::get_id() << " get both mutex"
            << "\n";
  std::scoped_lock lock(a.mut, b.mut);
  std::cout << "\n\tThread " << std::this_thread::get_id()
            << " access the Critical Section!\n";
}

int
main(int argc, char* argv[])
{
  CriticalData c1;
  CriticalData c2;

  std::thread t1([&c1, &c2] { deadlock(c1, c2); });
  std::thread t2([&c1, &c2] { deadlock(c2, c1); });

  t1.join();
  t2.join();

  std::cout << "\n";
}