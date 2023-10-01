// Example for C++17 in Detail

#include <iostream>
#include <optional>

int
main()
{
  std::optional<int> empty;
  std::optional<int> two(2);
  std::optional<int> ten(10);

  std::cout << std::boolalpha;
  std::cout << (ten > two) << "\n";
  std::cout << (ten < two) << "\n";
  std::cout << (empty < two) << "\n";
  std::cout << (empty == std::nullopt) << "\n";
  std::cout << (ten == 10) << "\n";
}