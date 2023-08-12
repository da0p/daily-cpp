#include <concepts>
#include <iostream>

/**
 * - A requires clause determines whether a function participates in overload
 * resolution or not. This happens beased on the value of a compile-time Boolean
 * expression.
 *
 * - A requirs expression determines whether a set of one or more expressions is
 * well-formed, without having any side effects on the behavior of the program.
 * A requires expression is a Boolean expression that can be used with a
 * requires clause.
 */

// requires expression
template<typename T>
concept addable = requires(T a, T b) { a + b; };

// requires clause
template<typename T>
  requires addable<T>
auto
add(T a, T b)
{
  return a + b;
}

// we can write like this, but absolutely not recommended
template<typename T>
  requires requires(T a, T b) { a + b; }
auto
add_2(T a, T b)
{
  return a + b;
}

int
main()
{
  add(1, 2);
  add_2(1, 2);
}