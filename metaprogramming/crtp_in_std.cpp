#include <functional>
#include <iostream>
#include <memory>
#include <thread>

/**
 * enabled_shared_from_this enables objects managed by a std::shared_ptr to
 * generate more std::shared_ptr instances in a safe manner.
 * The std::enabled_shared_from_this class is the base class in the CRTP
 * pattern.
 *
 */

struct building
{};

// crtp pattern here
struct building_2 : std::enable_shared_from_this<building_2>
{};

// another example for using enable_from_this
struct executor
{
  void execute(std::function<void(void)> const& task)
  {
    threads.push_back(std::thread([task]() {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(250ms);
      task();
    }));
  }
  ~executor()
  {
    for(auto& t : threads) {
      t.join();
    }
  }

private:
  std::vector<std::thread> threads;
};

struct building_3 : std::enable_shared_from_this<building_3>
{
  building_3() { std::cout << "building created\n"; }
  ~building_3() { std::cout << "building destroyed\n"; }

  void upgrade()
  {
    if(exec) {
      // without shared_from_this, but only this pointer, self is a raw pointer
      // not a shared_pointer. Raw pointer doesn't take part into managing
      // the lifetime of the object, thererfore undefined behavior
      exec->execute([self = shared_from_this()]() { self->do_upgrade(); });
    }
  }

  void set_executor(executor* e) { exec = e; }

private:
  void do_upgrade()
  {
    std::cout << "upgrading\n";
    operational = false;

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);

    operational = true;
    std::cout << "building is functional\n";
  }

  bool operational{false};
  executor* exec{nullptr};
};

int
main()
{
  building* b = new building();
  // ok
  std::shared_ptr<building> p1{b};
  // bad since p2 doesn't know about p1. We will have a double-free problem here
  // std::shared_ptr<building> p2{b};

  // instead if we use enable_shared_from_this as above
  building_2* b2 = new building_2();
  // then no more double-free problem
  std::shared_ptr<building_2> p3{b2};
  std::shared_ptr<building_2> p4{b2->shared_from_this()};

  executor e;
  std::shared_ptr<building_3> b3 = std::make_shared<building_3>();
  b3->set_executor(&e);
  b3->upgrade();

  std::cout << "main finished\n";
}