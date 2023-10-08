#include <iostream>

template<typename T>
constexpr std::string_view
typeName()
{
  constexpr auto prefix = std::string_view{"with T = "};
  constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
  auto const start = function.find(prefix) + prefix.size();
  return function.substr(start, function.find("; ") - start);
}

template<typename T, typename... Ts>
void
typeNames(char const* str)
{
  std::cout << str << typeName<T>();
  ((std::cout << ", " << typeName<T>()));
  ((std::cout << ", " << typeName<Ts>()), ...);
}

int
main()
{
  int num = 42;
  int& rnum = num;
  int const& crnum = num;
  auto c{num};
  auto c2{rnum};
  auto c3{crnum};

  typeNames<decltype(c), decltype(c2), decltype(c3)>("c, c2, c3: ");
  auto x{42};    // x is int
  auto y = 42;   // y is int
  auto z = {42}; // z is initializer_list<int>
  typeNames<decltype(x), decltype(y), decltype(z)>("\nx, y, z: ");

  struct Object
  {
    std::string str;
  };

  const Object unknown{"unknown"};
  Object const& refunknown = unknown;
  auto&& u = unknown;
  auto&& refu = refunknown;
  typeNames<decltype(u), decltype(refu)>("\nu and refu: ");
}