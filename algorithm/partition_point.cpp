#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};

  // std::partition_point works like std::upper_bound, but with an unary
  // predicate, but return the first element that does not satisfy the predicate
  auto pp =
    std::partition_point(data.begin(), data.end(), [](int v) { return v < 5; });

  // print 5
  std::cout << *pp << "\n";
}