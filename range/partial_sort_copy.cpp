#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int
main()
{
  std::vector<int> top(3);

  auto input = std::istream_iterator<int>(std::cin);
  auto cnt = std::counted_iterator(input, 10);

  std::ranges::partial_sort_copy(
    cnt, std::default_sentinel, top.begin(), top.end(), std::greater<>{}
  );
}