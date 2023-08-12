#include <concepts>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>

/**
 * Non-template functions that are members of class templates can be
 * constrained. This enables template classes to define member functions only
 * for types that satisfy some requirements.
 */

namespace A {
template<typename T>
struct wrapper
{
  T value;

  bool operator==(std::string_view str)
    requires std::is_convertible_v<T, std::string_view>
  {
    return value == str;
  }
};
}

namespace B {
// without concepts
template<typename T>
struct wrapper
{
  T value;

  template<
    typename U,
    typename = std::enable_if_t<
      std::is_copy_constructible_v<U> && std::is_convertible_v<U, T>>>
  wrapper(U const& v)
    : value(v)
  {
  }
};
}

namespace C {
// with concepts and constraints
template<typename T>
struct wrapper
{
  T value;

  wrapper(T const& v)
    requires std::is_copy_constructible_v<T>
    : value(v)
  {
  }
};
}

int
main()
{
  A::wrapper<int> a{42};
  A::wrapper<char const*> b{"42"};

  // error, does not satisfy constraint
  // auto x = a == 42;

  // ok
  auto y = b == "42";

  B::wrapper<int> c = 42;
  // cryptic error message
  // B::wrapper<std::unique_ptr<int>> d = std::make_unique<int>(42);

  C::wrapper<int> e = 42;
  // very much the same error as above
  // C::wrapper<std::unique_ptr<int>> f = std::make_unique<int>(42);

  return EXIT_SUCCESS;
}
