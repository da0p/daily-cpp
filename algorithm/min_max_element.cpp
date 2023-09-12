#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>
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

  // dangling references since it's invoked on a temporary range
  auto e = std::ranges::min_element(std::vector<int>{5, 3, -2, 0});
  // decltype(e) == std::ranges::dangling

  std::vector<int> data2 = {5, 3, -2, 0};
  // std::span sub-reference a range, and becomes a borrowed_range
  // no dangling reference
  auto f = std::ranges::min_element(std::span(data2.begin(), 2));
  std::cout << "*f = " << *f << "\n";
}