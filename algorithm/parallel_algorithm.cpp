#include <algorithm>
#include <atomic>
#include <execution>
#include <iostream>
#include <vector>

int
main()
{
  // Here we are using paralell unsequenced execution policy, that means cnt and
  // sum captured by reference in the lambda will be shared, therefore we need
  // to use either mutex or atomic
  std::atomic<int> cnt = 0, sum = 0;
  std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::for_each(
    std::execution::par_unseq,
    data.begin(),
    data.end(),
    [&](int el) {
      cnt++;
      sum += el;
    }
  );

  std::cout << "cnt = " << cnt << ", sum = " << sum << "\n";
}