#include <concepts>
#include <iostream>

/**
 * Type requirements are introduced with the keyword typename followed by the
 * name of a type.
 *
 * Type requirements can be used for several purposes:
 * - To verify that a nested type exists (such as in typename T::value_type;)
 * - To verify that a class template specialization names a type.
 * - To verify that an alias template specialization names a type.
 */
template<typename T>
concept KVP = requires {
  typename T::key_type;
  typename T::value_type;
};

template<typename T, typename V>
struct key_value_pair
{
  using key_type = T;
  using value_type = V;

  key_type key;
  value_type value;
};

template<typename T>
  requires std::is_arithmetic_v<T>
struct container
{};

template<typename T>
concept containerizeable = requires { typename container<T>; };

int
main()
{
  static_assert(containerizeable<int>);
  static_assert(!containerizeable<std::string>);
  static_assert(KVP<key_value_pair<int, std::string>>);
  static_assert(!KVP<std::pair<int, std::string>>);
}
