#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<double> data{1.2, 2.3, 3.1, 4.5, 7.1, 8.2};

  std::vector<int> out;

  // The transform view applies a transformation functor to every element of the
  // range
  std::ranges::copy(
    data | std::views::transform([](auto v) { return v * v; }),
    std::back_inserter(out)
  );

  for(auto v : out) {
    std::cout << v << " ";
  }
}