#include <cstdlib>
#include <ios>
#include <iostream>

struct foo
{
  int a;
};

struct bar
{
  int a = 0;
};

struct tar
{
  int a = 0;
  tar()
    : a(0)
  {
  }
};

int
main()
{
  std::cout << std::boolalpha;
  std::cout << std::is_trivial_v<foo> << "\n";
  std::cout << std::is_trivial_v<bar> << "\n";
  std::cout << std::is_trivial_v<tar> << "\n";
  std::cout << std::is_trivially_copyable_v<foo> << "\n";
  std::cout << std::is_trivially_copyable_v<bar> << "\n";
  std::cout << std::is_trivially_copyable_v<tar> << "\n";

  return EXIT_SUCCESS;
}