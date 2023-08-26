#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 6, 7, 8, 9};

  // std::equal_range returns both lower bound and upper bound
  auto [lb, ub] = std::equal_range(data.begin(), data.end(), 6);

  for(auto it = data.begin(); it != lb; it++) {
    std::cout << "[LOWER] " << *it << "\n";
  }

  for(auto it = lb; it != ub; it++) {
    std::cout << "[MIDDLE] " << *it << "\n";
  }

  for(auto it = ub; it != data.end(); it++) {
    std::cout << "[UPPER] " << *it << "\n";
  }
}