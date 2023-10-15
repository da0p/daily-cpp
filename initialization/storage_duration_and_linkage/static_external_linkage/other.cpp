#include "value.h"

extern Value v; // declaration only!

void
foo()
{
  std::cout << "in foo(): " << &v << "\n";
}