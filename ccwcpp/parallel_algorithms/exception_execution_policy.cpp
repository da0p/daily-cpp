#include <algorithm>
#include <execution>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int
main(int argc, char* arv[])
{
  std::vector<int> myVec{1, 2, 3, 4, 5};

  try {
    std::for_each(myVec.begin(), myVec.end(), []([[maybe_unused]] int _) {
      throw std::runtime_error("Without execution policy");
    });
  } catch(std::runtime_error const& e) {
    // exception can be captured here
    std::cout << e.what() << "\n";
  }

  try {
    std::for_each(
      std::execution::seq,
      myVec.begin(),
      myVec.end(),
      []([[maybe_unused]] int _) {
        // This exception won't be propagated.
        throw std::runtime_error("With execution policy");
      }
    );
    // with execution policy applied, exeception can't be propagated.
  } catch(std::runtime_error const& e) {
    std::cout << e.what() << "\n";
  } catch(...) {
    std::cout << "Catch-all exceptions"
              << "\n";
  }
}