#include <iostream>

template<typename T, typename U>
void
func(T a, U b)
{
  std::cout << "primary template\n";
}

template<>
void
func(int a, int b)
{
  std::cout << "int-int specialization\n";
}

template<>
void
func(int a, double b)
{
  std::cout << "int-double specialization\n";
}

int
main(int argc, char* argv[])
{
  func(1, 2);     // int-int specialization
  func(1, 2.0);   // int-double specialization
  func(1.0, 2.0); // primary template
}