#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

std::string
trim_left(std::string s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](auto&& c) {
            return !std::isspace(c);
          }));
  return s;
}

std::string
trim_right(std::string s)
{
  s.erase(
    std::find_if(
      s.rbegin(), s.rend(), [](auto&& c) { return !std::isspace(c); }
    ).base(),
    s.end()
  );

  return s;
}

int
main(int argc, char* argv[])
{
  constexpr auto str = "  C++ is a great language      ";
  auto trimmed_str = trim_left(trim_right(str));

  std::cout << trimmed_str << std::endl;

  assert("C++ is a great language" == trimmed_str);

  return 0;
}