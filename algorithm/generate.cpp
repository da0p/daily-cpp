#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  auto print = [](auto const& d) {
    for(auto const& v : d) {
      std::cout << v << " ";
    }
  };

  std::vector<int> data(5, 0);
  std::ranges::generate(data, []() { return 5; });
  print(data);

  std::cout << "\n\n";

  std::ranges::generate(data, [i = 0]() mutable { return i++; });
  print(data);
}