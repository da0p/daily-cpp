#include <algorithm>
#include <iostream>
#include <vector>

struct Record
{
  std::string label;
  int rank;
};

int
main()
{
  std::vector<Record> data{{"q", 1}, {"f", 1}, {"c", 2}, {"a", 1}, {"d", 3}};

  auto print = [&data] {
    for(auto d : data) {
      std::cout << "(" << d.label << ", " << d.rank << ")"
                << "\n";
    }
  };

  // std::stable_sort provides additional guarantee of preserving the relative
  // order of equal elements
  std::ranges::stable_sort(data, {}, &Record::label);
  print();

  std::cout << "\n\n";

  std::ranges::stable_sort(data, {}, &Record::rank);
  print();
}