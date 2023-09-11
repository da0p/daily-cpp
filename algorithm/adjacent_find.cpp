#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int
main()
{
  std::vector<int> data = {1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9};

  // The std::adjacent_find is a binary find algorithm that searches for pairs
  // of adjacent elements in  single range.
  // If the algorithm finds a pair of elements, it will return an iterator to
  // the first of two elements (end iterator otherwise)
  auto it1 = std::adjacent_find(data.begin(), data.end());
  std::cout << "Found: *it1 = " << *it1 << "\n";

  auto it2 = std::adjacent_find(data.begin(), data.end(), [](int l, int r) {
    return l + r > 10;
  });
  std::cout << "Found: *it2 = " << *it2 << "\n";
}