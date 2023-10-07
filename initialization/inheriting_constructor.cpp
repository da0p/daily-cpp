#include <iostream>

struct Base
{
  int x{};
  int y{};
  Base(int a, int b)
    : x{a}
    , y{b}
  {
  }

protected:
  Base() = default;
  Base(int a)
    : x{a}
  {
  }
};

struct Derived : public Base
{
  // This tells the complier that it can use all constructors from the base
  // class, ignoring access modifiers. It means that all public constructors are
  // visible and can be called, but the protected will still be protected in
  // that context.
  using Base::Base;
};

int
main()
{
  // Error: since Base::Base(int) is protected
  // Derived d{0};
  Derived d2{0, 1}; // fine
}