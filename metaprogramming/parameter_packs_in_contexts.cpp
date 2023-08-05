#include <array>
#include <iostream>

/// Template parameter list
/// This is for when you specify parameters for a template
template<typename... T>
struct outer
{
  template<T... args>
  struct innter
  {};
};
outer<int, double, char[5]> a;

/// Template argument list
/// This is when you specify arguments for a template
template<typename... T>
struct tag
{};

template<typename T, typename U, typename... Args>
void
tagger()
{
  tag<T, U, Args...> t1;
  tag<T, Args..., U> t2;
  tag<Args..., T, U> t3;
  tag<U, T, Args...> t4;
}

/// Function parameter list
/// This is for when you specify parameters for a function template

template<typename T>
void
make_it(T p)
{
  std::cout << p << " ";
}

template<typename T, typename... Args>
void
make_it(T p, Args... args)
{
  make_it(p);
  make_it(args...);
}

/// Function argument list
/// When the expansion pack appears inside the parenthesis of a funciton call
/// The largest expression or brace initialization list to the left of the
/// ellipsis is the pattern that is expanded.
template<typename T>
T
step_it(T value)
{
  return value + 1;
}

template<typename... T>
int
sum(T... args)
{
  return (... + args);
}

template<typename... T>
void
do_sums(T... args)
{
  /// sum(1, 2, 3, 4)
  auto s1 = sum(args...);

  /// sum(42, 1, 2, 3, 4)
  auto s2 = sum(42, args...);

  /// sum(step_it(1), step_it(2), ... step_it(4))
  auto s3 = sum(step_it(args)...);

  std::cout << "s1 = " << s1 << ", s2 = " << s2 << ", "
            << "s3 = " << s3 << "\n";
}

/// Parenthesized initializers
/// When the expansion pack appears inside the parenthesis of a direct
/// initializer, function-style cast, member initializer, new expression, and
/// other similar contexts, the rules are the same as for the context of
/// function argument lists
template<typename... T>
struct sum_wrapper
{
  sum_wrapper(T... args) { value = (... + args); }
  std::common_type_t<T...> value;
};

template<typename... T>
void
parenthesized(T... args)
{
  /// std::array<int, 4> {1, 2, 3, 4};
  std::array<std::common_type_t<T...>, sizeof...(T)> arr{args...};

  /// value = 1 + 2 + 3 + 4
  sum_wrapper sw1(args...);

  /// value = 2 + 3 + 4 + 5
  sum_wrapper sw2(++args...);
}

/// Brace-enclosed intializers
/// This is when you perform initialization using the brace notation
template<typename... T>
void
brace_enclosed(T... args)
{
  /// arr1: {1, 2, 3, 4, 0}
  int arr1[sizeof...(args) + 1] = {args..., 0};

  /// arr2: {2, 3, 4, 5}
  int arr2[sizeof...(args)] = {step_it(args)...};
}

/// Base specifiers and member initializer lists
/// A pack expansion may specify the list of base classes in a class
/// declaration. In addition, it may also appear in the member initializer list
/// as this may be necessary to call the constructors of the base classes
struct A
{};
struct B
{};
struct C
{};

template<typename T>
struct D
{
  T value;
};

template<typename... Bases>
struct X : public Bases...
{
  X(Bases const&... args)
    : Bases(args)...
  {
  }
};

template<typename T, template<typename> typename... Properties>
struct Y : public Properties<T>...
{
  Y(T value)
    : Properties<T>(value)...
  {
    std::cout << value << "\n";
  }
};

/// Using declarations
/// In the context of deriving from a pack of base classes, it may also be
/// useful to be able to introduce names from the base classes into the
/// definition of the derived class. Therefore, a pack expansion may also
/// appear in a using declaration.
struct E
{
  void execute() { std::cout << "E::execute\n"; }
};

struct F
{
  void execute() { std::cout << "F::execute\n"; }
};

struct G
{
  void execute() { std::cout << "G::execute\n"; }
};

/// Lambda captures
/// The capture clause of a lambda expression may contain a pack expansion
template<typename... T>
void
captures(T... args)
{
  auto l = [args...] { return sum(step_it(args)...); };
  std::cout << "sum_captures: " << l() << "\n\n";
}

template<typename... Bases>
struct Z : public Bases...
{
  Z(Bases const&... args)
    : Bases(args)...
  {
  }
  using Bases::execute...;
};

/// Fold expressions
/// template<typename... T>
/// int
/// sum(T... args)
/// {
///     return (... + args);
/// }

/// Alignment specifier
/// A pack expansion in an alignment specifier has the same effect as having
/// multiple alignas specifiers applied to the same declaration.
/// The parameter pack can be either a type or non-type pack
template<typename... T>
struct alignment1
{
  alignas(T...) char a;
};

template<int... args>
struct alignment2
{
  alignas(args...) char a;
};

/// Attribute list: not supported yet

int
main(int argc, char* argv[])
{
  make_it(42);
  std::cout << "\n\n";
  make_it(42, 41);

  std::cout << "\n\n";
  do_sums(1, 2, 3, 4);

  std::cout << "\n\n";
  parenthesized(1, 2, 3, 4);

  std::cout << "\n\n";
  brace_enclosed(1, 2, 3, 4);

  /// base specifiers and member initializer lists
  A a;
  B b;
  C c;
  X x(a, b, c);

  Y<std::string, D> y("Hello");
  Y<int, D> yy(1);
  std::cout << "yy.value = " << yy.value << "\n\n";

  E e;
  F f;
  G g;
  Z z(e, f, g);
  z.E::execute();
  z.F::execute();
  z.G::execute();

  captures(1, 2, 3, 4);

  alignment1<int, double> al1;
  alignment2<1, 4, 8> al2;
}