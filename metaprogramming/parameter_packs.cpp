#include <functional>
#include <iostream>

template<typename T, typename... Args>
T
sum(T a, Args... args)
{
  // Remember that this sizeof is applied on the parameter pack args.
  if constexpr(sizeof...(args) == 0) {
    return a;
  } else {
    return a + sum(args...);
  }
}

template<typename T>
T
sum_recur(T a)
{
  return a;
}

template<typename T, typename... Args>
T
sum_recur(T a, Args... args)
{
  return a + sum_recur(args...);
}

/// If the compiler can deduce the arguments, then a parameter pack can be
/// followed by other parameters including more parameter packs.
template<typename... Ts, typename... Us>
constexpr auto
multipacks(Ts... args1, Us... args2)
{
  std::cout << sizeof...(args1) << ", " << sizeof...(args2) << "\n";
}

template<typename... Ts, typename... Us>
constexpr auto
multipacks_verbose(Ts... args1, Us... args2)
{
  static_assert(
    sizeof...(args1) == sizeof...(args2), "Packs must be equal sizes."
  );
}

/// multiple parameter packs for variatic class template
template<typename, typename>
struct func_pair;

template<typename R1, typename... A1, typename R2, typename... A2>
struct func_pair<R1(A1...), R2(A2...)>
{
  std::function<R1(A1...)> f;
  std::function<R2(A2...)> g;
};

bool
twice_as(int a, int b)
{
  return a >= b * 2;
}

double
sum_and_div(int a, int b, double c)
{
  return (a + b) / c;
}

int
main(int argc, char* argv[])
{
  std::cout << "sum: " << sum(1, 2, 3, 4, 5) << "\n";
  std::cout << "sum_recur: " << sum_recur(1, 2, 3, 4, 5) << "\n";

  multipacks<int>(1, 2, 3, 4, 5, 6);

  multipacks<int, int, int>(1, 2, 3, 4, 5, 6);

  multipacks<int, int, int, int>(1, 2, 3, 4, 5, 6);

  multipacks<int, int, int, int>(1, 2, 3, 4, 5, 6);

  multipacks<int, int, double>(1, 2, 3.0, "s", 5.0, 6.0);

  /// Static assertion failes since two parameter packs are not equal
  // multipacks_verbose<int, int>(1, 2, 3, 4, 5);

  /// equal size of parameter packs
  multipacks_verbose<int, int>(1, 2, 3, 4);

  func_pair<bool(int, int), double(int, int, double)> funcs{
    twice_as, sum_and_div};
  funcs.f(42, 12);
  funcs.g(42, 12, 10.0);
}