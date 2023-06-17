#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int
main(int argc, char* argv[])
{
  std::vector<int> salaries = {1100, 2000, 500, 200, 900, 3000};

  auto print = [](auto&& salaries) {
    std::ostream_iterator<int> output(std::cout, " ");
    std::copy(salaries.begin(), salaries.end(), output);
  };
  print(salaries);
  std::cout << "\n----------------------------\n";
  auto salaryLowerThanAverageFilter = [](int i) { return i < 900; };
  // after parition, the elements that satify the predicate will be at
  // the beginning of the container, the reset will be at the end. Partition
  // doesn't guarantee previous order.
  auto it_1 = std::partition(
    salaries.begin(), salaries.end(), salaryLowerThanAverageFilter
  );
  print(salaries);
  // it_1 is an iterator pointing to the first element that doesn't satisfy the
  // unaryPredicate
  std::cout << "\n-----------------------------------\n";
  std::copy(it_1, salaries.end(), std::ostream_iterator<int>{std::cout, " "});

  auto ageHigherThan30 = [](auto&& age) { return age > 30; };

  std::cout << "\n-----------------------------\n";
  std::vector<int> ages = {10, 5, 45, 100, 90, 30};
  // stable_partition does guarantees previous order
  auto it_2 = std::stable_partition(ages.begin(), ages.end(), ageHigherThan30);
  print(ages);

  return 0;
}