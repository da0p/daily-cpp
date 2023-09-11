#include <algorithm>
#include <iostream>
#include <memory>

int
main()
{
  alignas(alignof(std::string)) char buffer[sizeof(std::string) * 10];
  auto* begin = reinterpret_cast<std::string*>(buffer);
  auto* it = begin;

  // The uninitialized algorithms cover the default initialization, value
  // initialization and copy initialization of elements.
  it = std::uninitialized_default_construct_n(it, 3);
  it = std::uninitialized_fill_n(it, 2, "Hello World!");
  it = std::uninitialized_value_construct_n(it, 3);
  it = std::uninitialized_fill_n(it, 2, "Bye World!");

  std::cout << *it << " ";

  std::destroy_n(begin, 10);
}