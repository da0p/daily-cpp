#include <algorithm>
#include <execution>
#include <iostream>
#include <iterator>
#include <vector>

struct LabeledValue
{
  int value;
  std::string label;
};

int
main()
{
  std::vector<LabeledValue> data1{{1, "first"}, {2, "first"}, {3, "first"}};
  std::vector<LabeledValue> data2{{0, "second"}, {2, "second"}, {4, "second"}};

  std::vector<LabeledValue> result;
  auto cmp = [](auto const& left, auto const& right) {
    return left.value < right.value;
  };

  std::ranges::merge(data1, data2, std::back_inserter(result), cmp);

  for(auto v : result) {
    std::cout << "[" << v.label << ", " << v.value << "]"
              << "\n";
  }

  std::cout << "\n\n";

  // Can't use back_inserter wrapper when use par_unseq policy
  std::vector<LabeledValue> output(data1.size() + data2.size(), LabeledValue{});
  std::merge(
    std::execution::par_unseq,
    data1.begin(),
    data1.end(),
    data2.begin(),
    data2.end(),
    output.begin(),
    cmp
  );
  for(auto v : output) {
    std::cout << "[" << v.label << ", " << v.value << "]"
              << "\n";
  }
}