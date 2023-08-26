#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{9, 8, 7, 6, 5, 4, 3, 2, 1};

  // std::partial_sort algorithm reorders the range's elements such that the
  // leading sub-range is in the same order it would when fully sorted. However,
  // the algorithm leaves the rest of the range in an unspecified order.
  // But the benefit of partial sort is faster runtime - approximately O(n *
  // logk), where k is the number of elements sorted.
  std::partial_sort(data.begin(), data.begin() + 3, data.end());
  // data == {1, 2, 3, --unspecified order-}
  for(auto d : data) {
    std::cout << d << " ";
  }

  std::cout << "\n\n";

  std::ranges::partial_sort(data, data.begin() + 3, std::greater<>());
  // data = {9, 8, 7, -unspecified order-}
  for(auto d : data) {
    std::cout << d << " ";
  }
}