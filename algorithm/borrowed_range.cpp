#include <algorithm>
#include <iostream>
#include <ranges>

int
main()
{
  // The range library ha the concepts of a borrowed range and a special type
  // std::ranges::danling. Borrowed ranges ar ranges that "borrow" their
  // elements from another range. Primary examples ar std::string_view and
  // std::span. For borrowed ranges, the lifetime of the elements is not tied
  // to the lifetime of the range itself.
  char const* c_str = "1234567890";

  // find on a temporary string_view
  auto sep1 = std::ranges::find(std::string_view(c_str), '0');
  // OK, std::string_view is a borrowed range, *sep1 = '0'
  std::cout << "*sep1 = " << *sep1 << "\n";

  int bad = 1234567890;

  // find on a temporary string
  auto sep2 = std::ranges::find(std::to_string(bad), '0');
  // bad, won't compile
  // std::cout << "*sep2 = " << *sep2 << "\n";
}