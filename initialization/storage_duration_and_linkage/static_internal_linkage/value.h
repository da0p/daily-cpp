#ifndef VALUE_H_
#define VALUE_H_

#include <iostream>

struct Value
{
  Value(int x)
    : v(x)
  {
    std::cout << "Value(" << v << ")\n";
  }
  ~Value() noexcept { std::cout << "~Value(" << v << ")\n"; }

  int v{0};
};

#endif