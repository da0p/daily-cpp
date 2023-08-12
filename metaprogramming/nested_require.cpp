#include <concepts>
#include <cstdlib>
#include <iostream>
#include <type_traits>

template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

// This concept contains one simple requirement and two nested requirements
// One nested requirement uses the are_same_v variable template whose value is
// determined by the conjunction of one or more type traits (std::is_same), and
// the other, the compile-time Boolean expression size...(T) > 1.
template<typename... T>
concept HomogeneousRange = requires(T... t) {
  (... + t);
  requires are_same_v<T...>;
  requires sizeof...(T) > 1;
};

template<typename... T>
auto
add(T&&... t)
  requires HomogeneousRange<T...>
{
  return (... + t);
}

int
main()
{
  add(1, 2);
  // error, types not the same
  // add(1, 2.0);
  // error, size not greater than 1
  // add(1);
  //
  // we can even test the concept
  static_assert(HomogeneousRange<int, int>);
  static_assert(!HomogeneousRange<int>);
  static_assert(!HomogeneousRange<int, double>);

  return EXIT_SUCCESS;
}
