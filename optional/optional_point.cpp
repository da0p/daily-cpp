#include <iostream>
#include <optional>

struct Point
{
  Point(int a, int b)
    : x(a)
    , y(b)
  {
  }

  int x;
  int y;
};

int
main()
{
  // will create a temporary object
  std::optional<Point> opt1{Point{0, 0}};

  // no temporary object created
  std::optional<Point> opt2{std::in_place, 0, 1};

  // no temporary object created
  auto opt3 = std::make_optional<Point>(0, 1);
}