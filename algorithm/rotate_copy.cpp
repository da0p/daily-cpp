#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> out;

  // std::rotate_copy algorithm will copy elements [middle, last], followed by
  // [first, middle], which mirrors the behavior of the std::rotate algorithm
  std::ranges::rotate_copy(data, data.begin() + 4, std::back_inserter(out));
  for(auto v : out) {
    std::cout << v << " ";
  }
}