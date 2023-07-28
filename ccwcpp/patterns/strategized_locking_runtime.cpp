#include <iostream>
#include <mutex>
#include <shared_mutex>

class Lock
{
public:
  virtual void lock() const = 0;
  virtual void unlock() const = 0;
};

class StrategizedLocking
{
private:
  Lock& lock;

public:
  StrategizedLocking(Lock& l)
    : lock(l)
  {
    lock.lock();
  }
  ~StrategizedLocking() { lock.unlock(); }
};

struct NullObjectMutex
{
  void lock() {}
  void unlock() {}
};

class NoLock : public Lock
{
  void lock() const override
  {
    std::cout << "NoLock::lock: "
              << "\n";
    nullObjectMutex.lock();
  }
  void unlock() const override
  {
    std::cout << "NoLocK::unlock: "
              << "\n";
    nullObjectMutex.unlock();
  }
  mutable NullObjectMutex nullObjectMutex;
};

class ExeclusiveLock : public Lock
{
  void lock() const override
  {
    std::cout << "ExcluiveLock::lock: "
              << "\n";
    mutex.lock();
  }
  void unlock() const override
  {
    std::cout << "ExclusiveLock::unlock: "
              << "\n";
    mutex.unlock();
  }
  mutable std::mutex mutex;
};

class SharedLock : public Lock
{
  void lock() const override
  {
    std::cout << "SharedLock::lock: "
              << "\n";
    sharedMutex.lock_shared();
  }
  void unlock() const override
  {
    std::cout << "SharedLock::unlock: "
              << "\n";
    sharedMutex.unlock_shared();
  }
  mutable std::shared_mutex sharedMutex;
};

int
main(int argc, char* argv[])
{
  NoLock noLock;
  StrategizedLocking stratLock1{noLock};
  {
    ExeclusiveLock exLock;
    StrategizedLocking stratLock2{exLock};
    {
      SharedLock sharLock;
      StrategizedLocking stratLock3{sharLock};
    }
  }
}