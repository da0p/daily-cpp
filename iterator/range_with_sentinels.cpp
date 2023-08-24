
#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

struct Sentinel
{
  using iter_t = std::vector<int>::iterator;
  iter_t begin;
  std::iter_difference_t<iter_t> cnt;
  // compare with another iterator, if it is not satisfied the following
  // requirement, then it's the end of the range
  bool operator==(iter_t const& l) const
  {
    return std::distance(begin, l) >= cnt;
  }
};

int
main()
{
  std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};

  auto it1 = data.begin();
  std::ranges::for_each(it1, Sentinel{it1, 5}, [](int e) {
    std::cout << e << ", ";
  });
}