#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int
main()
{
  std::list<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> out;

  // copy only n elements
  std::copy_n(data.begin(), 5, std::back_inserter(out));
  for(auto v : out) {
    std::cout << v << " ";
  }
}