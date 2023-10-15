#include "value.h"
#include <iostream>

// Static storage duration and external linkage
Value v{42};

void
foo();

int
main()
{
  std::cout << "in main(): " << &v << "\n";
  foo();
  // Automatic storage duration and no linkage
  Value x{100};

  std::cout << "main ends...\n";
}