#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

int
main()
{
  std::future<std::vector<int>> iotaFuture =
    std::async(std::launch::async, [startArg = 10]() {
      std::vector<int> numbers(100);
      std::iota(numbers.begin(), numbers.end(), startArg);
      std::cout << "calling from: " << std::this_thread::get_id()
                << " thread id\n";
      return numbers;
    });

  auto vec = iotaFuture.get();
  for(auto const& num : vec) {
    std::cout << num << ", ";
  }

  return 0;
}
