#include <concepts>
#include <cstdlib>
#include <iostream>

namespace X {
// conjunction
template<typename T>
  requires std::is_integral_v<T> && std::is_signed_v<T>
T
decrement(T value)
{
  return value--;
}

// disjunction
template<typename T>
  requires std::is_integral_v<T> || std::is_floating_point_v<T>
T
add(T a, T b)
{
  return a + b;
}
}

namespace Y {
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept Signed = std::is_signed_v<T>;

// conjunction
template<typename T>
concept SignedIntegral = Integral<T> && Signed<T>;

template<SignedIntegral T>
T
decrement(T value)
{
  return value--;
}

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

// disjunction
template<typename T>
concept Number = Integral<T> || FloatingPoint<T>;

template<Number T>
T
add(T a, T b)
{
  return a + b;
}
}

namespace Z {
// Conjunctions and disjunctions cannot be used to constrain template parameter
// packs. However, we can wrap the expression in a set of parentheses. Then
// the expression will become a fold expression. It is not a conjunction.
// Therefore, we get a single atomic constraint. The compiler will first check
// the correctness of the entire expression and then determine its Boolean
// value.
template<typename... T>
  requires(std::is_integral_v<T> && ...)
auto
add(T... args)
{
  return (... + args);
}
}

int
main()
{
  X::decrement(10);
  Y::decrement(10);

  return EXIT_SUCCESS;
}