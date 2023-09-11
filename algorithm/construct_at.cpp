#include <algorithm>
#include <iostream>
#include <string>

int
main()
{
  // std::construct_at, std::destroy_at algorithms will construct/destroy
  // a single element at a given address. If additional arguments are
  // specified, std::construct_at will forward these to the object's constructor
  alignas(alignof(std::string)) char mem[sizeof(std::string)];
  auto* ptr = reinterpret_cast<std::string*>(mem);

  std::construct_at(ptr, 8, 'X');
  std::cout << *ptr << "\n";
  std::destroy_at(ptr);
}