#include <algorithm>
#include <iostream>
#include <list>
#include <string>

struct X
{
  int rank;
  auto operator<=>(X const&) const = default;
};

int
main()
{
  int x = 10, y = 20;

  // The basic versions of std::min, std::max, and std::minmax operate on two
  // elements, accepting their arguments by const-reference and returning by
  // const-referenc. Unfortunately, this creates a
  // constness problem, and we also must be careful to capture the result by
  // value when passing in temporary objects.
  int min = std::min(x, y);

  std::string hello = "hello", world = "world";
  std::string& universe = const_cast<std::string&>(std::max(hello, world));
  universe = "universe";

  std::string greeting = hello + " " + world;

  int j = 20;
  auto& k = std::max(5, j);

  // Capturing the result by value gets a bit more complicated with std::minmax,
  // which returns a std::pair of const references. To avoid dangling references
  // to expired prvalues, we must explicitly name the result type.
  // Unfortunately, there is no way to work around this problem when using auto
  // or structured binding.
  X a{1}, b{2};
  auto [first, second] = std::minmax(b, a);

  std::pair<int, int> result = std::minmax(5, 10);

  // a variant that returns by value, resolves the danling reference issue, but
  // introducing potential for excessive copies.
  auto min_min = std::min({5, 3, -2, 0});
  // min_min = -2

  auto minmin_maxmax = std::minmax({5, 3, -2, 0});
  // minmin_maxmax.first == -2, minmin_maxmax.second == 5
  std::list<int> data{5, 3, -2, 0};
  auto maxmax = std::ranges::max(data);
  // maxmax == 5
}