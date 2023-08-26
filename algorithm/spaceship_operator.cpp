#include <cassert>
#include <iostream>

struct Point
{
  int x;
  int y;

  // pre-C++20 lexicographical less-than
  friend bool operator<(Point const& left, Point const& right)
  {
    if(left.x != right.x) {
      return left.x < right.x;
    }

    return left.y < right.y;
  }

  // default C++20 spaceship version of lexicographical comparison
  friend auto operator<=>(Point const&, Point const&) = default;

  // manual version of lexicographical comparison using operator <=>
  /*
  friend auto operator<=>(Point const& left, Point const& right)
  {
    if(left.x != right.x) {
      return left.x <=> right.x;
    }
    return left.y <=> right.y;
  }
  */
};

int
main()
{
  Point a{1, 2};
  Point b{2, 3};

  assert(a < b);
}