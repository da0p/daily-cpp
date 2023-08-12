#include <concepts>
#include <iostream>

namespace A {
int
add(int a, int b)
{
  return a + b;
}

template<typename T>
T
add(T a, T b)
{
  return a + b;
}
}

namespace B {
template<typename T>
T
add(T a, T b)
{
  return a + b;
}

template<typename T>
  requires std::is_integral_v<T>
T
add(T a, T b)
{
  return a + b;
}
}

namespace C {
template<typename T>
  requires(sizeof(T) == 4)
T
add(T a, T b)
{
  return a + b;
}

template<typename T>
  requires std::is_integral_v<T>
T
add(T a, T b)
{
  return a + b;
}
}

namespace D {
template<typename T>
  requires std::is_integral_v<T>
T
add(T a, T b)
{
  return a + b;
}

template<typename T>
  requires std::is_integral_v<T> && (sizeof(T) == 4)
T add(T a, T b)
{
  return a + b;
}
}

namespace E {

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
  requires Integral<T>
T
add(T a, T b)
{
  return a + b;
}

template<typename T>
  requires Integral<T> && (sizeof(T) == 4)
T add(T a, T b)
{
  return a + b;
}
}

int
main()
{
  // will use template in namespace A
  A::add(1.0, 2.0);

  // Both functions satisfy but the int version is more specialized
  A::add(1, 2);

  // Will use template version in namespace B
  B::add(1.0, 2.0);

  // will use one with constraint
  B::add(1, 2);

  // Will use version with integral constraint
  C::add((short)1, (short)2);

  // Both version in namespace C satisfies and are equally good matches.
  // compiler cannot choose the correct version --> trigger an error
  // C::add(1, 2);

  // even though there is a version that is more specialized, but the compiler
  // still triggers an error since we are not using concept.
  // D::add(1, 2);

  // But the compiler is able to choose the more specialized version if
  // concepts is used
  E::add(1, 2);

  return EXIT_SUCCESS;
}
