#include <iostream>
#include <variant>

int
main()
{
  // std::variant uses the memory in a similar way to union: so it will take
  // the max size of the underlying types. But since we need something that will
  // know that the currently active alternative is, then we need to use some
  // more space. Plus everything needs to honour the alignment rules.
  std::cout << "sizeof string: " << sizeof(std::string) << "\n";

  std::cout << "sizeof variant<int, string>: "
            << sizeof(std::variant<int, std::string>) << "\n";

  std::cout << "sizeof variant<int, float>: "
            << sizeof(std::variant<int, float>) << "\n";

  std::cout << "sizeof variant<int, double>: "
            << sizeof(std::variant<int, double>) << "\n";
}