#include <algorithm>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int
main(int argc, char* argv[])
{
  // transform_exclusive_scan and transform_inclusive_scan provide a way to
  // specify two functions to apply on elements of a container.
  // The unary operation will be applied first
  // Then the binary operation will be applied next
  std::vector<int> resVec3{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> resVec4(resVec3.size());
  std::transform_exclusive_scan(
    std::execution::par,
    resVec3.begin(),
    resVec3.end(),
    resVec4.begin(),
    0,
    std::plus{},      // then this will be applied second
    std::multiplies{} // this will be applied first
  );

  std::cout << "transform_exclusive_scan: ";
  for(auto v : resVec4) {
    std::cout << v << " ";
  }
  std::cout << "\n";

  std::vector<std::string> strVec{"This", "is", "my", "daily", "C++"};
  std::vector<int> resVec5(strVec.size());

  std::transform_inclusive_scan(
    std::execution::par,
    strVec.begin(),
    strVec.end(),
    resVec5.begin(),
    [](auto fir, auto sec) { return fir + sec; },
    [](auto s) { return s.length(); },
    static_cast<std::size_t>(0)
  );

  std::cout << "transform_inclusive_scan: ";
  for(auto v : resVec5) {
    std::cout << v << " ";
  }
  std::cout << "\n\n";

  return EXIT_SUCCESS;
}