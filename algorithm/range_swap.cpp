#include <iostream>
#include <ranges>

/**
 * C++20 rangified version of swap removes this complexity, and it will:
 *
 * - call the user-provided (found by ADL) overload of swap
 * - if that doesn't exist and the parameters are arrays of the same span,
 *   std::ranges::swap will behave as std::ranges::swap_ranges
 * - If the parameters are also not arrays, it will default to a move-swap.
 */

namespace Library {
struct Storage
{
  int value;
};

void
swap(Storage& left, Storage& right)
{
  std::cout << "Custom swap"
            << "\n";
  std::ranges::swap(left.value, right.value);
}
}

int
main()
{
  int a = 1, b = 2;

  // 3-step-swap
  std::ranges::swap(a, b);

  Library::Storage j{2}, k{3};
  // calls custom Library::swap()
  std::ranges::swap(j, k);
}