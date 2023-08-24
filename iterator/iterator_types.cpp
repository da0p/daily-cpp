#include <iostream>
#include <list>
#include <vector>

int
main()
{
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto it1 = arr.begin();

  // Ok, std::vector provides random access iterator
  it1 += 5;
  // Ok, provides advance operation
  ++it1;

  // Ok, random access iterator
  ptrdiff_t dst1 = it1 - arr.begin();

  std::list<int> lst = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto it2 = lst.begin();
  // Not Ok, list does not provide random access iterator
  // it2 += 5;

  // Ok, list provides advance operation
  ++it2;

  // Not Ok, list does not provide random access iterator
  // it2 - lst.begin();

  // Ok, linear calculation.
  ptrdiff_t dst2 = std::distance(lst.begin(), it2);
}