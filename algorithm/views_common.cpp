#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8};

  // std::views::common adapts a view into a range, a range with a begin and
  // an end iterator of matching types. Non-range versions of algorithms require
  // a common range.
  std::vector<int> out;
  auto view = data | std::views::filter([](int v) { return v % 2 == 0; }) |
              std::views::common;

  // Notice that this is not the range version
  std::copy(view.begin(), view.end(), std::back_inserter(out));
  // will print 2 4 6 8
  for(auto v : out) {
    std::cout << v << " ";
  }
}