#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int
main()
{
  std::vector<int> heights{1, 2, 3, 4, 5};
  std::vector<int> widths{2, 3, 4, 5, 6};

  // The std::inner_product algorithm is a left fold over two ranges. The pairs
  // of elements are first reduced and then accumulated.
  auto total_area =
    std::inner_product(heights.begin(), heights.end(), widths.begin(), 0);

  std::cout << "total_area = " << total_area << "\n";
}