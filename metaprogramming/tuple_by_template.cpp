#include <cstdlib>
#include <iostream>

/// Primary template
template<typename T, typename... Ts>
struct tuple
{
  tuple(T const& t, Ts const&... ts)
    : value(t)
    , rest(ts...)
  {
  }
  constexpr int size() const { return 1 + rest.size(); }
  T value;
  tuple<Ts...> rest;
};

template<typename T>
struct tuple<T>
{
  tuple(T const& t)
    : value(t)
  {
  }
  constexpr int size() const { return 1; }
  T value;
};

template<size_t N, typename T, typename... Ts>
struct nth_type : nth_type<N - 1, Ts...>
{
  static_assert(N < sizeof...(Ts) + 1, "Index out of bounds");
};

template<typename T, typename... Ts>
struct nth_type<0, T, Ts...>
{
  using value_type = T;
};

template<size_t N>
struct getter
{
  template<typename... Ts>
  static typename nth_type<N, Ts...>::value_type& get(tuple<Ts...>& t)
  {
    return getter<N - 1>::get(t.rest);
  }
};

template<>
struct getter<0>
{
  template<typename T, typename... Ts>
  static T& get(tuple<T, Ts...>& t)
  {
    return t.value;
  }
};

template<size_t N, typename... Ts>
typename nth_type<N, Ts...>::value_type&
get(tuple<Ts...>& t)
{
  return getter<N>::get(t);
}

int
main(int argc, char* argv[])
{
  tuple<int> one(42);
  tuple<int, double> two(10, 11);
  tuple<int, double, std::string> three(10, 11.0f, "Hello");

  std::cout << "one.value = " << one.value << "\n";
  std::cout << "two.value = " << two.value << "\n";
  std::cout << "two.rest.value = " << two.rest.value << "\n";
  std::cout << "three.value = " << three.value << "\n";
  std::cout << "three.rest.value = " << three.rest.value << "\n";
  std::cout << "three.rest.rest.value = " << three.rest.rest.value << "\n";

  tuple<int, double, std::string, char> four(42, 42.0f, "hello", 'h');
  std::cout << "get<2>(four) = " << get<2>(four) << "\n";

  return EXIT_SUCCESS;
}