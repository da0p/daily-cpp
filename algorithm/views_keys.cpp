#include <algorithm>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <vector>

int
main()
{
  auto print = [](auto const& d) {
    for(auto v : d) {
      std::cout << v << " ";
    }
    std::cout << "\n\n";
  };

  std::unordered_map<int, double> map{{0, 1.0}, {1, 1.5}, {2, 2.0}, {3, 2.5}};

  // std::views::keys and std::views::values operate on ranges of pair-like
  // elements. std::views::keys will produce a range of the first elements from
  // each pair. std::views::values will produce a range of the second elements
  // from each pair.

  std::vector<int> keys;
  std::ranges::copy(std::views::keys(map), std::back_inserter(keys));
  // keys == {0, 1, 2, 3} in unspecified order (std::unordered_map)
  print(keys);

  std::vector<double> values;
  std::ranges::copy(std::views::values(map), std::back_inserter(values));
  // values == {1.0, 1.5, 2.0, 2.5}
  // in unspecified order matching order of keys
  print(values);
}