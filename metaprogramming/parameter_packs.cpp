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

template<typename... Ts, typename... Us>
constexpr auto
multipacks(Ts... args1, Us... args2)
{
  std::cout << sizeof...(args1) << ", " << sizeof...(args2) << "\n";
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
}