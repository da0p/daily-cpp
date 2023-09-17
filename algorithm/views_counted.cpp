#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8};

  // std::views::counted adapts an iterator and number of elements into a view
  std::vector<int> out;
  std::ranges::copy(
    std::views::counted(std::next(data.begin()), 3), std::back_inserter(out)
  );
  for(auto v : out) {
    std::cout << v << " ";
  }
}