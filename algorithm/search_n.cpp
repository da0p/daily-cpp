#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data = {1, 0, 5, 8, 3, 3, 2};
  // The algorithm accepts the number of instances and the value to search
  // for as two consecutive arguments, followed by an optional custom
  // comparator function.
  auto it1 = std::search_n(data.begin(), data.end(), 2, 3);
  std::cout << "*it1 = " << *it1 << "\n";

  auto it2 = std::search_n(data.begin(), data.end(), 3, 3, [](int l, int r) {
    return l % 5 == r % 5;
  });
  std::cout << "*it2 = " << *it2 << "\n";

  auto it3 = std::search_n(data.begin(), data.end(), 2, 0);
  assert(it3 == data.end());
}