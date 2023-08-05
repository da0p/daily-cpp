#include <cstdlib>
#include <iostream>

template<typename T>
struct parser; // template declaration

// handle(double) definition
void
handle(double value)
{
  std::cout << "Processing a double: " << value << "\n";
}

// template definition
template<typename T>
struct parser
{
  void parse()
  {
    // non-dependent name
    handle(42);
  }
};

// handle(int) definition
void
handle(int value)
{
  std::cout << "Processing an int: " << value << "\n";
}

int
main()
{
  parser<int> p; // template instantiation

  // Will use handle(double) because handle(42) is a non-dependent name
  // That means it its name lookup will be performed at its definition
  p.parse();

  return EXIT_SUCCESS;
}