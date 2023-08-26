#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  // std::swap_ranges exchanges elements between two non-overlapping ranges
  // (potentially from the same container)
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // swap three first elements with the last three elements
  std::swap_ranges(data.begin(), data.begin() + 3, data.rbegin());

  for(auto e : data) {
    std::cout << e << " ";
  }
}