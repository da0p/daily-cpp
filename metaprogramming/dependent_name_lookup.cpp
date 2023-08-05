#include <cstdlib>
#include <iostream>

// template definition
template<typename T>
struct handler
{
  void handle(T value) { std::cout << "handler<T>: " << value << "\n"; }
};

// template definition
template<typename T>
struct parser
{
  void parse(T arg)
  {
    // dependent name
    arg.handle(42);
  }
};

// template specialization
template<>
struct handler<int>
{
  void handle(int value) { std::cout << "handler<int>: " << value << "\n"; }
};

int
main()
{
  handler<int> h;         // template instantiation
  parser<handler<int>> p; // template intantiation
  p.parse(h);
  return EXIT_SUCCESS;
}