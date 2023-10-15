#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutPrint;
thread_local int x = 0;

void
foo()
{
  thread_local int y = 0;
  std::lock_guard guard(mutPrint);
  std::cout << "in thread\t" << std::this_thread::get_id() << " ";
  std::cout << "&x " << &x << ", ";
  std::cout << "&y " << &y << "\n";
}

int
main()
{
  // when calling foo from the main thread, the address of x and y are the same
  // since they are declared as thread_local variables in main
  // However, x and y are different for thread worker1 and worker2 because they
  // are two different threads
  std::cout << "main    \t" << std::this_thread::get_id() << " &x " << &x
            << "\n";
  std::jthread worker1{foo};
  foo();
  std::jthread worker2{foo};
  foo();
}