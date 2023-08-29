#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int
main()
{
  auto print = [](auto const& data) {
    for(auto d : data) {
      std::cout << d << " ";
    }
    std::cout << "\n\n";
  };

  std::vector<int> data{2, 3, 5, 7, 11, 13};
  std::adjacent_difference(data.begin(), data.end(), data.begin());
  print(data);

  std::vector<int> data2(10, 1);
  // generate Fibonacci sequence
  std::adjacent_difference(
    data2.begin(),
    std::prev(data2.end()),
    std::next(data2.begin()),
    std::plus<int>()
  );
  print(data2);
}