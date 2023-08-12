#include <cstdlib>
#include <iostream>
#include <vector>

struct foo
{};

// Without concepts
template<typename T, typename U = void>
struct is_container : std::false_type
{};

template<typename T>
struct is_container<
  T,
  std::void_t<
    typename T::value_type,
    typename T::size_type,
    typename T::allocator_type,
    typename T::iterator,
    typename T::const_iterator,
    decltype(std::declval<T>().size()),
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end()),
    decltype(std::declval<T>().cbegin()),
    decltype(std::declval<T>().cend())>> : std::true_type
{};

template<typename T, typename U = void>
constexpr bool is_container_v = is_container<T, U>::value;

// With concepts
template<typename T>
concept container = requires(T t) {
  typename T::value_type;
  typename T::size_type;
  typename T::allocator_type;
  typename T::iterator;
  typename T::const_iterator;
  t.size();
  t.begin();
  t.end();
  t.cbedin();
  t.cend();
};

int
main()
{
  static_assert(!is_container_v<foo>);
  static_assert(is_container_v<std::vector<foo>>);

  static_assert(!container<foo>);
  static_assert(!container<std::vector<foo>>);

  return EXIT_SUCCESS;
}