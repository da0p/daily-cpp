#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

struct Student
{
  std::string name;
  int score;
};

int
main()
{
  std::vector<int> data1{1, 3, 5};
  std::vector<int> data2{2, 4, 6};

  // std::set_union algorithm produces a range containing elements present in
  // either of the ranges.
  std::vector<int> set_union;
  std::ranges::set_union(data1, data2, std::back_inserter(set_union));

  for(auto v : set_union) {
    std::cout << v << " ";
  }

  std::cout << "\n\n";

  auto cmp = [](auto const& l, auto const& r) { return l.score < r.score; };

  std::vector<Student> equal1{{"A", 1}, {"B", 1}, {"C", 2}};
  std::vector<Student> equal2{{"A", 1}, {"B", 1}, {"D", 2}};

  std::vector<Student> equal_union;
  std::ranges::set_union(equal1, equal2, std::back_inserter(equal_union), cmp);

  for(auto v : equal_union) {
    std::cout << v.name << ": " << v.score << "\n";
  }
}