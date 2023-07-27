#include <iostream>
#include <mutex>
#include <new>
#include <string>

class ScopedLock
{
private:
  std::mutex& mut;

public:
  explicit ScopedLock(std::mutex& m)
    : mut(m)
  {
    mut.lock();
    std::cout << "Lock the mutex: " << &mut << "\n";
  }
  ~ScopedLock()
  {
    std::cout << "Release the mutex: " << &mut << "\n";
    mut.unlock();
  }
};

int
main(int argc, char* argv[])
{
  // NOTE:
  // scoped_lock will have undefined behavior when there is the need of
  // recursive mutex
  std::mutex mutex1;
  ScopedLock scopedLock1{mutex1};

  std::cout << "\nBefore local scope"
            << "\n";
  {
    std::mutex mutex2;
    ScopedLock scopedLock2{mutex2};
  }
  std::cout << "After local scope"
            << "\n";

  std::cout << "\nBefore try-catch block"
            << "\n";

  try {
    std::mutex mutex3;
    ScopedLock scopedLock3{mutex3};
    // exception is thrown here, scoped lock will go out of scoped, the
    // destructor will be called and release the lock
    throw std::bad_alloc();
  } catch(std::bad_alloc& e) {
    std::cout << e.what();
  }
  std::cout << "\nAfter try-catch block"
            << "\n";
  // Remember that a longjmp in C doesn't call the destructor, hence, won't
  // release the lock
}