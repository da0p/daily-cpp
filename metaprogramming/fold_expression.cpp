#include <cstdlib>
#include <iostream>

/// Unary right fold
template<typename... Args>
void
print(Args... args)
{
  ((std::cout << args << " "), ...);
}

/// Unary left fold
template<typename... Args>
uint32_t
sum_1(Args... args)
{
  return (... + args);
}

/// Unary right fold
template<typename... Args>
uint32_t
sum_2(Args... args)
{
  return (args + ...);
}

/// Binary left fold
template<typename... Args>
uint32_t
sum_3(uint32_t init, Args... args)
{
  return (init + ... + args);
}

/// Binary right fold
template<typename... Args>
uint32_t
sum_4(uint32_t init, Args... args)
{
  return (args + ... + init);
}

int
main(int argc, char* argv[])
{

  print(1, 2, 3, 4);
  std::cout << "\n";
  print(sum_1(1, 2, 3, 4));
  std::cout << "\n";
  print(sum_2(1, 2, 3, 4));
  std::cout << "\n";
  print(sum_3(1, 2, 3, 4));
  std::cout << "\n";
  print(sum_4(1, 2, 3, 4));
  std::cout << "\n";

  return EXIT_SUCCESS;
}