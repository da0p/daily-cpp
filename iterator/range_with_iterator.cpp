#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7};

  auto it1 = data.begin();
  auto it2 = it1 + 3;

  std::for_each(it1, it2, [](auto i) { std::cout << i << " "; });
  // should print 1 2 3

  std::cout << "\n\n";

  auto it3 = it2 + 3;
  std::for_each(it2, it3, [](auto i) { std::cout << i << " "; });
  // should print 4 5 6
}