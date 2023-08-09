#include <cstdlib>
#include <iostream>

/**
 * - decltype is usually used in templates together with the auto specifier
 *
 * - decltype specifier is not restricted for use in template code. It can be
 *   used with different expressions, and it yields different results based on
 *   the expression. The rules are as follows:
 *   1. If the expression is an identifier or a class member access, then the
 *      result is the type of the entity that is named by the expression. If
 *      the entity does not exist, or it is a function that has an overload set
 *      (more than one function with the same name exists), then the compiler
 *      will generate an error.
 *   2. If the expression is a function call or an overloaded operator function,
 *      then the result is the return type of the function. If the overloaded
 *      operator is wrapped in parentheses, these are ignored.
 *   3. If the expression is an lvalue, then the result type is an lvalue
 *      reference to the type of expression.
 *   4. If the expression is something else, then the result type is the type
 *      of the expression.
 */
int
f()
{
  return 42;
}

int
g()
{
  return 0;
}

int
g(int a)
{
  return a;
}

struct wrapper
{
  int val;
  int get() const { return val; }
};

int a = 42;
int& ra = a;
double const d = 42.99;
long arr[10];
long l = 0;
char* p = nullptr;
char c = 'x';
wrapper w1{1};
wrapper* w2 = new wrapper{2};

/**
 * There are several more rules for data member access
 *
 * - The const or volatile specifiers of the object used in the decltype
 *   expression do not contribute to the deduced type.
 * - Whether the object or pointer expression is an lvalue or an rvalue does
 *   not affect the deduced type.
 * - If the data member access expression is parenthesized, such as
 *   decltype(expression), then the previous two rules do not apply. The const
 *   or volatile qualifier of the object does affect the deduced type,
 *   including the valueness of the object.
 */
struct foo
{
  int a = 0;
  int volatile b = 0;
  int const c = 42;
};

foo fx;
foo const cf;
foo volatile* pf = &fx;

int x = 1;
int volatile y = 2;
int const z = 3;

template<typename T, typename U>
decltype(auto)
minimum(T&& a, U&& b)
{
  return a < b ? a : b;
}

// decltype(auto) for perfect forward reference return
template<typename T>
T const&
func(T const& ref)
{
  return ref;
}

template<typename T>
decltype(auto)
func_caller(T&& ref)
{
  return func(std::forward<T>(ref));
}

int
main()
{
  decltype(a) e1;      // R1, int
  decltype(ra) e2 = a; // R1, int&
  decltype(f) e3;      // R1, int()
  decltype(f()) e4;    // R2, int
  // decltype(g) e5;           // R1, error
  decltype(g(1)) e6;         // R2, int
  decltype(&f) e7 = nullptr; // R4, int(*)()
  decltype(d) e8 = 1;        // R1, const double
  decltype(arr) e9;          // R1, long[10]
  // decltype(arr[1]) e10 = 1;  // R3, long&
  decltype(w1.val) e11;      // R1, int
  decltype(w1.get()) e12;    // R1, int
  decltype(w2->val) e13;     // R1, int
  decltype(w2->get()) e14;   // R1, int
  decltype(42) e15 = 1;      // R4, int
  decltype(1 + 2) e16;       // R4, int
  decltype(a + 1) e17;       // R4, int
  decltype(a = 0) e18 = a;   // R3, int&
  decltype(p) e19 = nullptr; // R1, char*
  decltype(*p) e20 = c;      // R3 char&
  decltype(p[0]) e21 = c;    // R3, char&

  // other rules
  decltype(fx.a) e22 = 0; // int
  decltype(fx.b) e23 = 0; // int volatile
  decltype(fx.c) e24 = 0; // int const

  decltype(cf.a) e25 = 0; // int
  decltype(cf.b) e26 = 0; // int volatile
  decltype(cf.c) e27 = 0; // int const

  decltype(pf->a) e28 = 0;   // int
  decltype(pf->b) e29 = 0;   // int volatile
  decltype(pf->c) e30 = 0;   // int const
  decltype(foo{}.a) e31 = 0; // int
  decltype(foo{}.b) e32 = 0; // int volatile
  decltype(foo{}.c) e33 = 0; // int const

  // if double parentheses, rules are reversed. Const and volatile do affect
  // the deduced type.
  decltype((fx.a)) e34 = x; // int&
  decltype((fx.b)) e35 = y; // int volatile&
  decltype((fx.c)) e36 = z; // int const&

  decltype((fx.a)) e37 = x; // int const&
  decltype((fx.b)) e38 = y; // int const volatile&
  decltype((fx.c)) e39 = z; // int const&

  decltype((pf->a)) e40 = x; // int volatile&
  decltype((pf->b)) e41 = y; // int volatile&
  decltype((pf->c)) e42 = z; // int const volatile&

  decltype((foo{}.a)) e43 = 0; // int&&
  decltype((foo{}.b)) e44 = 0; // int volatile&&
  decltype((foo{}.c)) e45 = 0; // int const&&

  auto mi = minimum(10, 11.2);

  int n = 42;
  decltype(func(a)) r1 = func(a);               // int const&
  decltype(func_caller(a)) r2 = func_caller(a); // int const&

  return EXIT_SUCCESS;
}