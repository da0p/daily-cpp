#include <concepts>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <vector>

template<std::floating_point T>
constexpr T PI = T(3.141592653L);

template<std::integral T>
using integral_vector = std::vector<T>;

int
main()
{
  std::cout << PI<double> << "\n";
  // error
  // std::cout << PI<int> << "\n";

  integral_vector<int> v1{1, 2, 3};

  // error
  // integral_vector<double> v2 {1.0, 2.0, 3.0};

  return EXIT_SUCCESS;
}
