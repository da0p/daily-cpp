#include <algorithm>
#include <iostream>
#include <vector>

int
main()
{
  // The nth_element algorithm is a partitioning algorithm that ensures that the
  // element in the nth position is the element that would be in this position
  // if the range was sorted.
  std::vector<int> data{9, 1, 8, 2, 7, 3, 6, 4, 5};
  std::nth_element(data.begin(), data.begin() + 4, data.end());
  // data[4] == 5, data[0..3] < data[4]
  for(auto d : data) {
    std::cout << d << " ";
  }

  std::cout << "\n\n";

  std::nth_element(
    data.begin(), data.begin() + 7, data.end(), std::greater<>()
  );
  // data[7] == 2, data[0..6] > data[7]
  for(auto d : data) {
    std::cout << d << " ";
  }
}