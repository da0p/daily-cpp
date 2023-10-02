#include <any>
#include <cassert>
#include <iostream>
#include <vector>

class MyType
{
  int a, b;

public:
  MyType(int x, int y)
    : a(x)
    , b(y)
  {
  }
};

int
main()
{
  std::any a;
  assert(!a.has_value());

  a = MyType(10, 11);
  a = std::string("Hello");

  a.emplace<float>(100.5f);
  a.emplace<std::vector<int>>({10, 11, 12, 13});
  a.emplace<MyType>(10, 11);
}