#include <cstdlib>
#include <iostream>
#include <map>

template<typename T>
struct base_parser
{
  using value_type = T;
};

template<typename T>
struct parser : base_parser<T>
{

  void parse()
  {
    // This line does not work because it's a non-dependent name and therefore
    // it will not be looked up in the base base class, only in the enclosing
    // scope.
    // value_type v{};
    //
    // This line does not work neither because the compiler can not assume this
    // is actually a type. A specialization of base_parser may follow and
    // value_type could be defined as something else than a type.
    // base_parser<T>::value_type v{};
    //
    // In order to fix it
    typename base_parser<T>::value_type v{};

    std::cout << "parse\n";
  }
};

struct dictionary_traits
{
  using key_type = int;
  using map_type = std::map<key_type, std::string>;
  static constexpr int identity = 1;
};

template<typename T>
struct dictionary : T::map_type
{
  int start_key{T::identity};
  // before C++20, before T::key_type, T::map_type::mapped_type, you need
  // typename
  T::key_type next_key;

  using value_type = T::map_type::mapped_type;

  void add(T::key_type const&, value_type const&) {}
};

int
main()
{
  parser<int> parser;
  parser.parse();

  dictionary<dictionary_traits> d;

  return EXIT_SUCCESS;
}