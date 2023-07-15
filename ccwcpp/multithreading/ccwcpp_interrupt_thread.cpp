#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>

int
main(int argc, char* argv[])
{
  std::jthread nonInterruptable([] {
    int counter{0};
    while(counter < 10) {
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      std::cerr << "nonInterruptable: " << counter << "\n";
      ++counter;
    }
  });

  std::jthread interruptable([](std::stop_token token) {
    int counter{0};
    while(counter < 10) {
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      if(token.stop_requested())
        return;
      std::cerr << "interruptable: " << counter << "\n";
      ++counter;
    }
  });

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cerr << "\n";
  std::cerr << "Main thread interrupts both jthreads"
            << "\n";
  nonInterruptable.request_stop();
  interruptable.request_stop();

  std::cout << "\n";
}
