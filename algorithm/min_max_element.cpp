#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data = {5, 3, -2, 0};

  // std::min_element algorithm returns an iterator to the minimum
  auto i = std::min_element(data.begin(), data.end());
  std::cout << "*i = " << *i << "\n";

  auto j = std::max_element(data.begin(), data.end());
  std::cout << "*j = " << *j << "\n";

  auto k = std::minmax_element(data.begin(), data.end());
  std::cout << "*k.first = " << *k.first << ", *k.second = " << *k.second
            << "\n";
}