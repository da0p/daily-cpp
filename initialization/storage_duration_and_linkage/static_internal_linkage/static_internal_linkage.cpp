#include "value.h"
#include <iostream>

// static storage duration and internal linkage
static Value v{42};

void
foo();

int
main()
{
  std::cout << "in main(): " << &v << "\n";
  foo();
  std::cout << "main ends...\n";
}
