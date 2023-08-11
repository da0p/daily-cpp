#include <iostream>

template<typename T>
struct foo
{
  using foo_type = T;
};

template<typename T>
struct bar
{
  using bar_type = T;
};

using int_foo = foo<int>;
using int_bar = bar<int>;

// There is a comma in decltype, that means if decltype can't deduce from the
// first one, it will ignore and move to check the second argument. It's void().
template<typename T>
decltype(typename T::foo_type(), void())
handle(T const& v)
{
  std::cout << "handle a foo\n";
}

template<typename T>
decltype(typename T::bar_type(), void())
handle(T const& v)
{
  std::cout << "handle a bar\n";
}

int
main()
{
  int_foo fi;
  int_bar bi;
  int x = 0;
  handle(fi);
  handle(bi);

  // error
  // handle(x);
}