#include <functional>
#include <iostream>
#include <string>

int
main(int argc, char* argv[])
{
  const std::string in{"Hello World"};
  const std::string out = std::invoke(
    [copy = in](int x) mutable {
      copy.replace(copy.find("World"), 5, "C++");
      copy += std::to_string(x);
      return copy;
    },
    10
  );
  std::cout << out;
}
