#include <iostream>
#include <map>
#include <vector>

///
/// @note: An alias template is a name that refers not to a type but a family of
/// types. A template is not a class, function, or a variable but a blueprint
/// that allows the creation of a family of types, functions, or variables.
///

// This is an alias template. It defines a family of types.
template<typename T>
using customer_addresses_t = std::map<int, std::vector<T>>;

struct delivery_address_t
{};
struct invoice_address_t
{};

// Introduce two type aliases
using customer_delivery_addresses_t = customer_addresses_t<delivery_address_t>;

using customer_invoice_addresses_t = customer_addresses_t<invoice_address_t>;

// Alias templates can appear at namespace or class scope just like any template
// declaration. On the other hand, they can neither be fully nor partially
// specialized.
// In order to overcome this limitation, a solution is to create a class
// template with a type alias member and specialize the class. Then you can
// create an alias template that refers to the type alias member.

// In this example, there are two partial template specializations
template<typename T, size_t S>
struct list
{
  using type = std::vector<T>;
};

template<typename T>
struct list<T, 1>
{
  using type = T;
};

template<typename T, size_t S>
using list_t = typename list<T, S>::type;

int
main(int argc, char* argv[])
{
  // partial template specialization will deduce to the correct type
  static_assert(std::is_same_v<list_t<int, 1>, int>);
  static_assert(std::is_same_v<list_t<int, 2>, std::vector<int>>);
}