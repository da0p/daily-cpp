#include <iostream>
#include <mutex>
#include <thread>

/**
 * Advantages of thread-safe interface:
 *
 * - A recursive call of a mutex is not possible.
 * - The program uses minimal locking and, therefore, minimal synchronization.
 *   Using just a std::recursive_mutex in each public or private member function
 *   of the class Critical would end in a more expensive synchronizations.
 * - From the user perspective, Critical is straightforward to use because
 *   synchronization is only an implementation detail.
 *
 * Disadvantages:
 * - Each interface member function delegates its work to the corresponding
 *   implementation member function. The indirection overhead is a typical
 *   disadvantage of the thread-safe interface pattern.
 */
class Critical
{
public:
  void interface1() const
  {
    std::lock_guard<std::mutex> lockGuard(mut);
    implementation1();
  }
  void interface2() const
  {
    std::lock_guard<std::mutex> lockGuard(mut);
    implementation2();
    implementation3();
    implementation1();
  }

private:
  void implementation1() const
  {
    std::cout << "implementation1: " << std::this_thread::get_id() << "\n";
  }
  void implementation2() const
  {
    std::cout << "implementation2: " << std::this_thread::get_id() << "\n ";
  }
  void implementation3() const
  {
    std::cout << "implementation3: " << std::this_thread::get_id() << "\n";
  }

  mutable std::mutex mut;
};

int
main()
{
  std::thread t1([] {
    const Critical crit;
    crit.interface1();
  });

  std::thread t2([] {
    Critical crit;
    crit.interface2();
    crit.interface1();
  });

  Critical crit;
  crit.interface1();
  crit.interface2();

  t1.join();
  t2.join();
}