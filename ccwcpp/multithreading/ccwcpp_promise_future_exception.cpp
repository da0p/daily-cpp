#include <cstdlib>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

struct Div
{
  void operator()(std::promise<int>&& intPromise, int a, int b)
  {
    try {
      if(b == 0) {
        std::string errMsg = std::string("Illegal division by zero: ") +
                             std::to_string(a) + "/" + std::to_string(b);
        throw std::runtime_error(errMsg);
      }
      intPromise.set_value(a / b);
    } catch(...) {
      // Not like task, promise doesn't capture automatically the exception
      // it provides only the facility to keep the shared state.
      intPromise.set_exception(std::current_exception());
    }
  }
};

void
executeDivision(int nom, int denom)
{
  std::promise<int> divPromise;
  std::future<int> divResult = divPromise.get_future();

  Div div;
  std::thread divThread(div, std::move(divPromise), nom, denom);

  // get the result or the exception
  try {
    std::cout << nom << "/" << denom << " = " << divResult.get() << "\n";
  } catch(std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }
  divThread.join();
}

void
executeDivisionAsync(int nom, int denom)
{
  auto div = std::async(std::launch::async, [nom, denom] {
    if(denom == 0) {
      std::string errMsg = std::string("Illegal division by zero!");
      throw std::runtime_error(errMsg);
    }

    return nom / denom;
  });

  try {
    auto result = div.get();
    std::cout << nom << "/" << denom << " = " << result << "\n";
  } catch(std::exception& e) {
    std::cout << e.what() << "\n";
  }
}

int
main(int argc, char* argv[])
{
  // using promise member functiont to set exception state
  executeDivision(20, 0);
  executeDivision(20, 10);

  // function in async throws, kept in shared state. When fut.get(), it's
  // rethrown.
  executeDivisionAsync(20, 0);
  executeDivisionAsync(20, 10);

  return EXIT_SUCCESS;
}