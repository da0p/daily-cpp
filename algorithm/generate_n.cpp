#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int
main()
{
  auto print = [](auto const& d) {
    for(auto const& v : d) {
      std::cout << v << " ";
    }
  };

  std::vector<int> data;

  std::fill_n(std::back_inserter(data), 5, 11);
  // data == {11, 11, 11, 11, 11};
  print(data);

  std::cout << "\n\n";

  std::ranges::generate_n(std::back_inserter(data), 5, []() { return 7; });
  // data == {11, 11, 11, 11, 11, 7, 7, 7, 7, 7}
  print(data);
}