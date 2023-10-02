#include <iostream>
#include <variant>

int
main()
{
  // There are four ways o change the current value of the variant
  // - the assignment operator
  // - emplace
  // - get and then assign a new value for the currently active type
  // - a visitor ( you cannot change the type, but you can change the value
  //   of the current alternative)

  std::variant<int, float, std::string> intFloatString{"Hello"};

  // Change to int
  intFloatString = 10;

  // Change to string
  intFloatString.emplace<2>(std::string("Hello"));

  // std::get returns a reference, so you can change the value
  std::get<std::string>(intFloatString) += std::string(" World");
  std::cout << "intFloatString = " << std::get<std::string>(intFloatString)
            << "\n";

  intFloatString = 10.1f;
  if(auto pFloat = std::get_if<float>(&intFloatString); pFloat) {
    *pFloat *= 2.0f;
  }
}