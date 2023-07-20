#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int
main(int argc, char* argv[])
{
  std::vector<int> intVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::for_each_n(std::execution::par, intVec.begin(), 5, [](int& arg) {
    arg *= arg;
  });
  std::cout << "for_each_n: ";
  for(auto v : intVec) {
    std::cout << v << " ";
  }
  std::cout << "\n\n";

  // exclusive_scan and inclusive_scan
  // exclusive_scan exclude the last element from calculation
  std::vector<int> resVec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::exclusive_scan(
    resVec.begin(), resVec.end(), resVec.begin(), 1, std::multiplies{}
  );

  std::cout << "exclusive_scan: ";
  for(auto v : resVec) {
    std::cout << v << " ";
  }
  std::cout << "\n\n";

  std::vector<int> resVec2{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // inclusive_scan does not exclude the last element from calculation
  std::inclusive_scan(
    std::execution::par,
    resVec2.begin(),
    resVec2.end(),
    resVec2.begin(),
    [](int fir, int sec) { return fir * sec; }
  );

  std::cout << "inclusive_scan: ";
  for(auto v : resVec2) {
    std::cout << v << " ";
  }
  std::cout << "\n\n";

  return EXIT_SUCCESS;
}