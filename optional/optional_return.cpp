#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

std::vector<int>
createVec()
{
  std::vector<int> v{0, 1, 2, 3, 4};
  std::cout << std::hex << v.data() << "\n";
  // return {std::move(v)}; // this one will cause a copy
  return (v); // this one moves
  // return v;  // this one will moves as well
}

std::optional<std::vector<int>>
createOptVec()
{
  std::vector<int> v{0, 1, 2, 3, 4};
  std::cout << std::hex << v.data() << "\n";
  return {v}; // this one will cause a copy
  // return v; // this one moves
}

std::optional<std::string>
createOptStr()
{
  std::string s{"Hello Super Long String"};
  std::cout << std::hex << static_cast<void*>(s.data()) << "\n";
  // return {s} // this one will cause a copy
  return s; // this one will move
}

std::unique_ptr<int>
createPtr()
{
  std::unique_ptr<int> p;
  // return {p}; // uses copy of unique_ptr and it won't compile
  return p; // this one moves, therefore it compiles
}

int
main()
{
  std::cout << "createVec:\n\n";
  auto v1 = createVec();
  std::cout << std::hex << v1.data() << "\n\n";

  std::cout << "createOptVec:\n\n";
  auto v2 = createOptVec();
  std::cout << std::hex << v2->data() << "\n\n";

  std::cout << "createOptStr:\n\n";
  auto v3 = createOptStr();
  std::cout << std::hex << static_cast<void*>(v3->data()) << "\n\n";

  auto p = createPtr();
}