#include <concepts>
#include <iostream>

/**
 * Function using auto for function parameters is called an abbreviated function
 * template.
 *
 */
auto
add(auto a, auto b)
{
  return a + b;
}

// Since abbreviated function template is a regular function with a simplified
// syntax, we can specialize it. This category of abbreviated function templates
// is called unconstrained. There is no restriction on the template arguments.
// However, it is possible to provide constraints for their parameters with
// concepts. Abbreviated function templates that use concepts are called
// constrained.
// Full specialization template<>
auto
add(char const* a, char const* b)
{
  return std::string(a) + std::string(b);
}

auto
add_3(std::integral auto a, std::integral auto b)
{
  return a + b;
}

auto
add_4(std::integral auto... args)
{
  return (... + args);
}

int
main()
{
  add(4, 2);
  add(4.0, 2);
  add("Hello ", "World");
  add_3(4, 2);

  // error, 4.2 is not integral
  // add_3(4.2, 2);

  add_4(1, 2, 3, 4);

  // we can constrain auto in lambda function
  auto lsum = [](std::integral auto a, std::integral auto b) { return a + b; };
  lsum(1, 2);
  // error
  // lsum(1, 2.0);
}