#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8};

  std::vector<int> even;
  // std::views::filter consists of all elements that satisfy the provided
  // predicate
  std::ranges::copy(
    data | std::views::filter([](int v) { return v % 2 == 0; }),
    std::back_inserter(even)
  );

  for(auto v : even) {
    std::cout << v << " ";
  }
}