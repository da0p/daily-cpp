#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> out;

  // std:;reverse_copy algorithm copies elements in reverse order
  // std::reverse_copy does not permit the source, and the destination ranges to
  // overlap
  std::ranges::reverse_copy(data, std::back_inserter(out));
  for(auto v : out) {
    std::cout << v << " ";
  }
}