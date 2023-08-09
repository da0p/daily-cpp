#include <cstdlib>
#include <iostream>
#include <vector>

// forwarding reference
template<typename T>
void
f(T&& arg)
{
  std::cout << "f(T&&)\n";
}

// rvalue reference
template<typename T>
void
f(T const&& arg)
{
  std::cout << "f(T const&&)\n";
}

// rvalue reference
template<typename T>
void
f(std::vector<T>&& arg)
{
  std::cout << "f(vector<T>&&)\n";
}

// rvalue reference because f is not a template but a non-template member
// function of a class template, so the rule for forwarding references does not
// apply.
template<typename T>
struct S
{
  void f(T&& arg) { std::cout << "S.f(T&&)\n"; }
};

int
main()
{
  int x = 42;
  f(x);  // f(T&&)
  f(42); // f(T&&)
  int const cx = 100;
  f(cx);            // f(T&&)
  f(std::move(cx)); // f(T const&&)

  std::vector<int> v{42};
  f(v);                    // f(T&&)
  f(std::vector<int>{42}); // f(T const&&)

  S<int> s;
  // s.f(x)     // error, can't bind lvalue to rvalue reference
  s.f(42); // S.f(T&&);
  return EXIT_SUCCESS;
}