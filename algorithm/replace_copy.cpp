#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> out, odd;

  // std::replace_copy, the algorithm will replace elements matching a value
  // for std::replace_copy_if, the algorithm will replace elements for which
  // the predicate evaluates to true.
  std::ranges::replace_copy(data, std::back_inserter(out), 5, 10);
  for(auto v : out) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";
  auto is_even = [](int v) { return v % 2 == 0; };
  std::ranges::replace_copy_if(data, std::back_inserter(odd), is_even, -1);
  for(auto v : odd) {
    std::cout << v << " ";
  }
}