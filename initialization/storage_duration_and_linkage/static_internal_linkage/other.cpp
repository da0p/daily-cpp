#include "value.h"

// static storage duration and internal linkage
static Value v{100};

void
foo()
{
  std::cout << "in foo(): " << &v << "\n";
}