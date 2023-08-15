#include <iostream>
#include <type_traits>

/**
 * A type list is a compile-time construct that enables us to manage a sequence
 * of types. A typelist is somehow similar to a typle but does not store any
 * data. A typelist only carries type information and is used exlusively at
 * compile-time for implementing different metaprogramming algorithms, type
 * switches, or design patterns such as Abstract Factory or Visitor.
 *
 */

template<typename... Ts>
struct typelist
{};

namespace detail {
template<typename TL>
struct length;

template<template<typename...> typename TL, typename... Ts>
struct length<TL<Ts...>>
{
  using type = std::integral_constant<std::size_t, sizeof...(Ts)>;
};
}

template<typename TL>
using length_t = typename detail::length<TL>::type;

template<typename TL>
constexpr std::size_t length_v = length_t<TL>::value;

struct empty_type
{};
namespace detail {
template<typename TL>
struct front_type;

template<template<typename...> typename TL, typename T, typename... Ts>
struct front_type<TL<T, Ts...>>
{
  using type = T;
};

template<template<typename...> typename TL>
struct front_type<TL<>>
{
  using type = empty_type;
};
}

template<typename TL>
using front_t = typename detail::front_type<TL>::type;

namespace detail {
template<typename TL>
struct back_type;

template<template<typename...> typename TL, typename T, typename... Ts>
struct back_type<TL<T, Ts...>>
{
  using type = back_type<TL<Ts...>>::type;
};
template<template<typename...> typename TL, typename T>
struct back_type<TL<T>>
{
  using type = T;
};

template<template<typename...> typename TL>
struct back_type<TL<>>
{
  using type = empty_type;
};
}

template<typename TL>
using back_t = typename detail::back_type<TL>::type;

namespace detail {
template<std::size_t I, std::size_t N, typename TL>
struct at_type;

template<
  std::size_t I,
  std::size_t N,
  template<typename...>
  typename TL,
  typename T,
  typename... Ts>
struct at_type<I, N, TL<T, Ts...>>
{
  using type =
    std::conditional_t<I == N, T, typename at_type<I, N + 1, TL<Ts...>>::type>;
};

template<std::size_t I, std::size_t N>
struct at_type<I, N, typelist<>>
{
  using type = empty_type;
};
}

template<std::size_t I, typename TL>
using at_t = typename detail::at_type<I, 0, TL>::type;

namespace detail {
template<typename TL, typename T>
struct push_back_type;

template<template<typename...> typename TL, typename T, typename... Ts>
struct push_back_type<TL<Ts...>, T>
{
  using type = TL<Ts..., T>;
};

template<typename TL, typename T>
struct push_front_type;

template<template<typename...> typename TL, typename T, typename... Ts>
struct push_front_type<TL<Ts...>, T>
{
  using type = TL<T, Ts...>;
};

template<typename TL>
struct pop_front_type;

template<template<typename...> typename TL, typename T, typename... Ts>
struct pop_front_type<TL<T, Ts...>>
{
  using type = TL<Ts...>;
};

template<template<typename...> typename TL>
struct pop_front_type<TL<>>
{
  using type = TL<>;
};

template<std::ptrdiff_t N, typename R, typename TL>
struct pop_back_type;

template<std::ptrdiff_t N, typename... Ts, typename U, typename... Us>
struct pop_back_type<N, typelist<Ts...>, typelist<U, Us...>>
{
  using type =
    typename pop_back_type<N - 1, typelist<Ts..., U>, typelist<Us...>>::type;
};

template<typename... Ts, typename... Us>
struct pop_back_type<0, typelist<Ts...>, typelist<Us...>>
{
  using type = typelist<Ts...>;
};

template<typename... Ts, typename U, typename... Us>
struct pop_back_type<0, typelist<Ts...>, typelist<U, Us...>>
{
  using type = typelist<Ts...>;
};

template<>
struct pop_back_type<-1, typelist<>, typelist<>>
{
  using type = typelist<>;
};
}

template<typename TL, typename T>
using push_back_t = typename detail::push_back_type<TL, T>::type;

template<typename TL, typename T>
using push_front_t = detail::push_front_type<TL, T>::type;

template<typename TL>
using pop_front_t = typename detail::pop_front_type<TL>::type;

template<typename TL>
using pop_back_t = typename detail::pop_back_type<
  static_cast<std::ptrdiff_t>(length_v<TL>) - 1,
  typelist<>,
  TL>::type;

int
main()
{
  static_assert(length_t<typelist<int, double, char>>::value == 3);
  static_assert(length_v<typelist<int, double, char>> == 3);
  static_assert(length_v<typelist<int, double>> == 2);
  static_assert(length_v<typelist<int>> == 1);

  static_assert(std::is_same_v<front_t<typelist<>>, empty_type>);
  static_assert(std::is_same_v<front_t<typelist<int>>, int>);
  static_assert(std::is_same_v<front_t<typelist<int, double, char>>, int>);

  static_assert(std::is_same_v<back_t<typelist<>>, empty_type>);
  static_assert(std::is_same_v<back_t<typelist<int, double>>, double>);
  static_assert(std::is_same_v<back_t<typelist<int>>, int>);

  static_assert(std::is_same_v<at_t<0, typelist<>>, empty_type>);
  static_assert(std::is_same_v<at_t<0, typelist<int>>, int>);
  static_assert(std::is_same_v<at_t<0, typelist<int, char>>, int>);
  static_assert(std::is_same_v<at_t<1, typelist<>>, empty_type>);
  static_assert(std::is_same_v<at_t<1, typelist<int, char>>, char>);
  static_assert(std::is_same_v<at_t<2, typelist<>>, empty_type>);
  static_assert(std::is_same_v<at_t<2, typelist<int>>, empty_type>);
  static_assert(std::is_same_v<at_t<2, typelist<int, char>>, empty_type>);

  static_assert(std::is_same_v<pop_back_t<typelist<>>, typelist<>>);
  static_assert(std::is_same_v<pop_back_t<typelist<double>>, typelist<>>);
  static_assert(std::is_same_v<
                pop_back_t<typelist<double, char>>,
                typelist<double>>);
  static_assert(std::is_same_v<
                pop_back_t<typelist<double, char, int>>,
                typelist<double, char>>);
}