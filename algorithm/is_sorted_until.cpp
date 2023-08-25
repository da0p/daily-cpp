#include <algorithm>
#include <bits/ranges_util.h>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data{1, 4, 5, 7, 9, 2, 3};

  // std::is_sorted_until returns the first element that is out of order
  auto found = std::is_sorted_until(data.begin(), data.end());
  if(found != data.end()) {
    std::cout << "First out-of-order element = " << *found << "\n";
  }

  // iterate over the sorted sub-range
  std::for_each(data.begin(), found, [](auto i) { std::cout << i << " "; });

  std::cout << "\n";

  // another way
  for(auto v : std::ranges::subrange(data.begin(), found)) {
    std::cout << v << " ";
  }
}