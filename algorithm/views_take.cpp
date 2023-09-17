#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{1, 3, 5, 7, 2, 4, 6, 8, 9};
  std::vector<int> out1;
  // std::views::take will take a specified number of elements
  std::ranges::copy(data | std::views::take(3), std::back_inserter(out1));
  // out1 = {1, 3, 5}
  for(auto v : out1) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";

  std::vector<int> out2;
  // std::views::take_while will take elemenets that satisfies the predicate
  // from the beginning until it does not
  std::ranges::copy(
    data | std::views::take_while([](int v) { return v % 2 != 0; }),
    std::back_inserter(out2)
  );
  // out2 = {1, 3, 5, 7}
  for(auto v : out2) {
    std::cout << v << " ";
  }
}