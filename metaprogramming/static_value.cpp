#include <iostream>

template<typename T>
struct foo
{
  static T value;
};

// provide a default value for any instatiation
template<typename T>
T foo<T>::value = 0;

// provide a default value for full specialization for int
template<>
int foo<int>::value = 42;

template<typename>
struct bar
{}; // primary template

template<>
struct bar<int>; // explicit specialization declaration

int
main(int argc, char* argv[])
{
  // We expect a and b have the same value, but not c
  foo<double> a, b;
  foo<int> c;

  a.value = 100;
  std::cout << "a.value = " << a.value << "\n";
  std::cout << "b.value = " << b.value << "\n";
  std::cout << "c.value = " << c.value << "\n";

  // bar<T> is the primary template for which a declaraction of an explicit
  // specialization for the int type exists. This makes it possible to use
  // bar<double> and bar<int>* (declaring pointers to partial types is
  // supported). However, at the point of declaring the z variable, the complete
  // type bar<int> is not available, since a definition of the full
  // specialization for int is missing.
  bar<double> x;
  bar<int>* y;
  // bar<int> z;
}