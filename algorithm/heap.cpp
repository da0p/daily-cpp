#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

int
main()
{
  auto print = [](auto const& data) {
    for(auto v : data) {
      std::cout << v << " ";
    }
    std::cout << "\n\n";
  };

  std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::make_heap(data.begin(), data.end());
  print(data);

  std::make_heap(data.begin(), data.end(), std::greater<>{});
  print(data);

  std::vector<int> data2 = {1, 1, 2, 2};
  std::make_heap(data2.begin(), data2.end());
  data2.push_back(9);
  print(data2);
  std::push_heap(data2.begin(), data2.end());

  data2.push_back(7);
  print(data2);
  std::push_heap(data2.begin(), data2.end());

  std::pop_heap(data2.begin(), data2.end());
  print(data2);

  std::pop_heap(data2.begin(), std::prev(data2.end()));
  print(data2);

  // std::sort_heap will reorder the elements in a heap into a sorted order.
  // The algorithm has O(nlogn) complexity.
  std::vector<int> data3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::make_heap(data3.begin(), data3.end());
  print(data3);
  std::sort_heap(data3.begin(), data3.end());
  print(data3);

  std::vector<int> data4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  bool test1 = std::is_heap(data4.begin(), data4.end());
  std::cout << std::boolalpha;
  std::cout << "test1 = " << test1 << "\n";
  auto it1 = std::is_heap_until(data4.begin(), data4.end());
  std::cout << "is_heap_until: value = " << *it1 << "\n";

  std::make_heap(data4.begin(), data4.end());

  bool test2 = std::is_heap(data4.begin(), data4.end());
  std::cout << "test2 = " << test2 << "\n";

  auto it2 = std::is_heap_until(data4.begin(), data4.end());
  std::cout << "is_heap_until: value = " << *it2 << "\n";
}