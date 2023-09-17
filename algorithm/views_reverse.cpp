#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4};

  std::vector<int> out;
  std::ranges::copy(data | std::views::reverse, std::back_inserter(out));
  // out == {4, 3, 2, 1}
  for(auto v : out) {
    std::cout << v << " ";
  }
}