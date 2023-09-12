#include <algorithm>
#include <iostream>

int
main()
{
  int a = std::ranges::clamp(10, 0, 20);
  // a == 10 since 10 > 0 and 10 < 20;
  std::cout << "a = " << a << "\n";

  int b = std::clamp(-20, 0, 20);
  // b == 0 since -20 < 0
  std::cout << "b = " << b << "\n";

  int c = std::clamp(30, 0, 20);
  // c == 20 since 30 > 20
  std::cout << "c = " << c << "\n";

  int x = 10, y = 20, z = 30;
  // This means std::clamp returns a const reference
  // const_cast just throws away const, so we can modify.
  int& w = const_cast<int&>(std::clamp(z, x, y));
  w = 99;

  std::cout << "x = " << x << ", y = " << y << ", z = " << z << "\n";
}