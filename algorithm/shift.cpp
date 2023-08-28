#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  auto print = [](auto const& data) {
    for(auto v : data) {
      std::cout << v << " ";
    }
  };
  // std::shift_left and std::shift_right algorithms move elements in the
  // provided range by the specified amount of positions. But unlike
  // std::rotate, shift algorithm does not wrap around
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::shift_left(data.begin(), data.end(), 3);
  print(data);
  // should print 4 5 6 7 8 9 7 8 9

  std::cout << "\n\n";

  std::shift_right(data.begin(), data.end(), 3);
  print(data);
  // should print 4 5 6 4 5 6 7 8 9
}