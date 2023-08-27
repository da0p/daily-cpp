#include <algorithm>
#include <bits/ranges_algo.h>
#include <iostream>
#include <iterator>
#include <vector>

int
main()
{
  std::vector<int> data1{1, 3, 5, 7, 9};
  std::vector<int> data2{3, 4, 5, 6, 7};

  // std::set_symmetric_difference provides elements that presents only on one
  // range but not both
  std::vector<int> sym_diff;
  std::ranges::set_symmetric_difference(
    data1, data2, std::back_inserter(sym_diff)
  );

  for(auto v : sym_diff) {
    std::cout << v << " ";
  }
}