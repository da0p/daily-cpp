#include <iostream>

template<typename T>
struct base_parser
{
  void init() { std::cout << "base_parser::init\n"; }
};

template<typename T>
struct parser : base_parser<T>
{
  void parse()
  {
    // This will not work because init() is a non-dependennt name
    // At this point of the definition, it must be known. Although
    // base_parser<T>::init exists, the compiler cannot assume it's what
    // we want to call because the primary template base_parser can be later
    // specialized and init can be defined as something else (such as type,
    // or a variable, or another function, or it may be missing entirely).
    // Therefore, name lookup does not happen in the base class, only on its
    // enclosing scope, and there is no function called init in parser.
    //
    // init();

    // Instead, if init is invoked via this pointer, it will become dependent
    // name, and its name binding is moved from the point of template definition
    // to the point of template instantiation.
    this->init();
    std::cout << "parser::parse\n";
  }
};

// If we provide a specialization for int
template<>
struct base_parser<int>
{
  void init() { std::cout << "specialized init\n"; }
};

int
main()
{
  // This will invoke the specialized init function
  parser<int> p;
  p.parse();

  // There is no specialized init function with double type
  // it will invoke the non-specialized version
  parser<double> p2;
  p2.parse();
}