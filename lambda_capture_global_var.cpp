#include <iostream>
#include <string>

int global = 10;

int
main(int argc, char* argv[])
{
  std::cout << global << "\n";
  auto foo = [=] mutable noexcept { ++global; };
  foo();
  std::cout << global << "\n";
  auto const increaseGlobal = []() noexcept { ++global; };
  increaseGlobal();
  std::cout << global << "\n";
  auto const moreIncreaseGlobal = [global]() noexcept { ++global; };
  moreIncreaseGlobal();
  std::cout << global << "\n";
  return 0;
}
