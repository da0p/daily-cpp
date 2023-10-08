#include <array>
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct S
{
  S()
    : numbers{1, 2, 3, 4}
    , doubles{0.1, 1.1, 2.1}
    , ints{100, 101, 102}
    , moreInts(10, 1)
    , names(10, "hello")
    , mapping{{"one", 1}, {"two", 2}}
  {
  }

  int numbers[4];
  // int nums[]; // need to provide the size!
  std::array<double, 3> doubles;
  std::vector<int> ints;
  std::vector<int> moreInts;
  std::vector<std::string> names;
  std::map<std::string, int> mapping;
};

void
foo(std::initializer_list<int> list)
{
  if(!std::empty(list)) {
    for(auto& x : list) {
      std::cout << x << ", ";
    }
    std::cout << "(" << list.size() << " elements)\n";
  } else {
    std::cout << "empty list\n";
  }
}

int
main()
{
  S s;
  std::cout << "s.numbers[0]: " << s.numbers[0] << "\n";
  std::cout << "s.double[0]: " << s.doubles[0] << "\n";
  std::cout << "s.ints[0]: " << s.ints[0] << "\n";
  std::cout << "s.moreInts[9]: " << s.moreInts[9] << "\n";
  std::cout << "s.names[9]: " << s.names[9] << "\n";
  std::cout << "s.mapping[\"one\"]: " << s.mapping["one"] << "\n";

  std::cout << "\n\n";
  foo({});
  foo({1, 2, 3});
  foo({1, 2, 3, 4, 5});

  return 0;
}