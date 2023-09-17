#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::vector<std::tuple<int, int, std::string>> data{
    {1, 100, "Cat"}, {2, 99, "Dog"}, {3, 17, "Car"}};

  auto print = [](auto const& data) {
    for(auto v : data) {
      std::cout << v << " ";
    }
    std::cout << "\n\n";
  };

  // The std::views::elements will produce a range of the Nth elements from a
  // range of tuple-like elements.
  std::vector<int> second;
  std::ranges::copy(data | std::views::elements<1>, std::back_inserter(second));
  // should print 100 99 17
  print(second);

  std::vector<std::string> third;
  std::ranges::copy(data | std::views::elements<2>, std::back_inserter(third));
  // should print Cat Dog Car
  print(third);
}
