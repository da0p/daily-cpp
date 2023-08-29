#include <algorithm>
#include <iostream>
#include <numeric>
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

  std::vector<int> data(6, 1);
  // data == {1, 1, 1, 1, 1, 1}
  std::cout << "Initial data:\n";
  print(data);

  std::partial_sum(data.begin(), data.end(), data.begin());
  // data == {1, 2, 3, 4, 5, 6}
  std::cout << "partial sum: \n";
  print(data);

  std::vector<int> out;
  std::partial_sum(
    data.begin(), data.end(), std::back_inserter(out), std::multiplies<>{}
  );
  // out == {1, 2, 6, 24, 120, 720}
  std::cout << "partial_sum (with std::multiplies): \n";
  print(data);
}