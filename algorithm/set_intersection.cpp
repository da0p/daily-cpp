#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

struct Student
{
  std::string name;
  uint32_t score;
};

int
main()
{
  std::vector<int> data1{1, 2, 3, 4, 5};
  std::vector<int> data2{2, 4, 6};

  // std::ranges::set_intersection produces a range containing the elements that
  // are present in both ranges.
  std::vector<int> intersection;
  std::ranges::set_intersection(data1, data2, std::back_inserter(intersection));

  for(auto v : intersection) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";

  auto cmp = [](auto const& l, auto const& r) { return l.score < r.score; };

  std::vector<Student> equal1{{"A", 100}, {"B", 100}, {"C", 200}};
  std::vector<Student> equal2{{"D", 100}, {"E", 200}, {"F", 200}};
  std::vector<Student> intersection2;
  std::ranges::set_intersection(
    equal1, equal2, std::back_inserter(intersection2), cmp
  );

  for(auto v : intersection2) {
    std::cout << v.name << ", " << v.score << "\n";
  }
}