#include <iostream>

template<int... R>
constexpr int Sum = (... + R);

int
main()
{
  std::cout << Sum<1, 2, 3> << "\n";
}