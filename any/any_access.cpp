#include <any>
#include <iostream>
#include <string>
#include <vector>

struct MyType
{
  int a, b;

  MyType(int x, int y)
    : a(x)
    , b(y)
  {
  }

  void print() { std::cout << a << ", " << b << "\n"; }
};

int
main()
{
  std::any var = std::make_any<MyType>(10, 10);
  try {
    std::any_cast<MyType&>(var).print();
    std::any_cast<MyType&>(var).a = 11; // read/write
    std::any_cast<MyType&>(var).print();
    std::any_cast<int>(var); // throw
  } catch(std::bad_any_cast const& e) {
    std::cout << e.what() << "\n";
  }

  int* p = std::any_cast<int>(&var);
  std::cout << (p ? "contains int... \n" : "doesn't contain an int...\n");
  if(MyType* pt = std::any_cast<MyType>(&var); pt) {
    pt->a = 12;
    std::any_cast<MyType&>(var).print();
  }
}