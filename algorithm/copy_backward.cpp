#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int
main()
{
  auto print = [](auto const& d) {
    for(auto const& v : d) {
      std::cout << v << " ";
    }
    std::cout << "\n\n";
  };

  std::vector<std::string> data{"a", "b", "c", "d", "e", "f"};
  std::vector<std::string> out(9, "");

  // std::copy_backward and std::move_backward are variants that copy in the
  // opposite direction, starting at the back of the range.
  std::copy_backward(data.begin(), data.end(), out.end());
  print(out);

  std::copy_backward(data.begin(), std::prev(data.end()), data.end());
  print(data);
}