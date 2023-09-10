#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int
main()
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> even, odd, no_five;

  auto is_even = [](int v) { return v % 2 == 0; };

  // std::copy_if copies elements that satify the predicate
  std::ranges::copy_if(data, std::back_inserter(even), is_even);
  for(auto v : even) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";

  // std::remove_copy_if copies elements that do not satisfy the predicate
  std::ranges::remove_copy_if(data, std::back_inserter(odd), is_even);
  for(auto v : odd) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";
  // std::remove_copy copies element except the specified element
  std::ranges::remove_copy(data, std::back_inserter(no_five), 5);
  for(auto v : no_five) {
    std::cout << v << " ";
  }
}