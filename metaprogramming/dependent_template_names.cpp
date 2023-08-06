#include <cstdlib>
#include <iostream>

template<typename T>
struct base_parser
{
  template<typename U>
  void init()
  {
    std::cout << "init\n";
  }
};

template<typename T>
struct parser : base_parser<T>
{
  void parse()
  {
    // In this case, the dependent name is a template. The default behavior
    // of the compiler is to interpret the dependent name as a non-type, which
    // leads to errors concerning the usage of the comparison operator <.
    //
    // base_parser<T>::init<int>(); // error
    // If we put template keyword here, we tell the compiler that the dependent
    // name is a template.
    // Keep in mind that the template keyword can only follow the scope
    // resolution operator(::), member access through pointer(->), and the
    // member access (.)
    base_parser<T>::template init<int>();
    std::cout << "parse\n";
  }
};

// The dependent name does not have to be a function template. It can also be
// a class template
template<typename T>
struct base_parser_2
{
  template<typename U>
  struct token
  {};
};

template<typename T>
struct parser_2 : base_parser_2<T>
{
  void parse()
  {
    using token_type = base_parser_2<T>::template token<int>;
    token_type t1{};

    typename base_parser_2<T>::template token<int> t2{};

    std::cout << "parser\n";
  }
};

int
main()
{
  parser<int> parser;
  parser.init<int>();

  parser_2<int> parser_2;
  parser_2.parse();

  return EXIT_SUCCESS;
}
