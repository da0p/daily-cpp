#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

struct Student
{
  std::string name;
  uint32_t id;
};

int
main()
{
  std::vector<int> data1{1, 2, 3, 4, 5, 6};
  std::vector<int> data2{3, 4, 5};

  std::vector<int> difference;

  // std::ranges::set_difference returns a range of elements present in the
  // first range but not in the second range
  std::ranges::set_difference(data1, data2, std::back_inserter(difference));

  for(auto v : difference) {
    std::cout << v << " ";
  }

  auto cmp = [](auto const& l, auto const& r) { return l.id < r.id; };

  std::vector<Student> equal1{
    {"John", 1102}, {"Anna", 1102}, {"Linda", 1102}, {"Peter", 1102}};

  std::vector<Student> equal2{{"Alice", 1102}, {"Carl", 1102}};

  // For equivalent elements, where the first range contains M such elements and
  // the second range contains N such elements, the result will ocntain the last
  // std::max(M - N, 0) such elements from the firs range.
  std::vector<Student> equal_diff;
  std::ranges::set_difference(
    equal1, equal2, std::back_inserter(equal_diff), cmp
  );

  std::cout << "\n\n";

  for(auto s : equal_diff) {
    std::cout << "Name: " << s.name << ", id: " << s.id << "\n";
  }
}