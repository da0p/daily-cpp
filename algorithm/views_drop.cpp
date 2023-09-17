#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<int> data{1, 3, 5, 7, 2, 4, 6, 8};

  std::vector<int> out1;
  // std::views::drop will drop a specified number of elements
  std::ranges::copy(data | std::views::drop(3), std::back_inserter(out1));
  // out1 == {7, 2, 4, 6, 8};
  for(auto v : out1) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";

  std::vector<int> out2;
  std::ranges::copy(
    data | std::views::drop_while([](int v) { return v % 2 != 0; }),
    std::back_inserter(out2)
  );
  // out2 == {2, 4, 6, 8}
  for(auto v : out2) {
    std::cout << v << " ";
  }
}