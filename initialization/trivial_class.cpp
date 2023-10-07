#include <iostream>

// note: default constructors are not user-provided.
//
// A trivial class is a class that i trivially copyable and has one or more
// eligible default constructors, all of which are trivial.
//
// A trivially copyable class is a class:
// - that has at least one eligible copy constructor, move constructor, copy
//   assignment operator, or move assignment operatr.
// - where each eligible copy constructor, move constructor, copy assignment
//   operator, and move assignment operator is trivial, and
// - that has a trivial, non-deleted destructor.
//
//
// A default constructor is trivial if it is not user-provided and if:
// - its class has no virtual functions and no virtual base classes, and
// - no non-static data member of its class has a default member initializer,
//   and all the direct base classes of its class have trivial default
//   constructors, for all the non-static data membes of its class that are of
//   class type ( or array thereof), each such class has a trivial default
//   constructor.
//
// A copy/move constructor for class X is trivial if it is not user-provided and
// - class X has no virtual functions and no virtual base classes, and
// - the constructor selected to copy/move each direct base class subobject is
//   trivial, and
// - for each non-static data member of X that is of class type (or array
//   thereof), the constructor selected to copy/move that member is trivial;
//
// Implications of trivial types
// - Trivial types occupy a contiguous memory area (including padding)
// - They are "mem-copyable", so you can convert them into a byte array, and
//   read it back.
// - Trivial types cannot be declared const without an initializer.
// - Whwn a trivial type is zero-initialized (for example, through value
//   initialization {}), its data members will also be zero-initialized.
//

// default constructors
struct MyType0
{
  int x;
};

struct MyType1
{
  MyType1() {}
  int x;
};

// default constructors
struct MyType2
{
  MyType2() = default;
  int x;
};

struct MyType3
{
  MyType3();
  int x;
};

MyType3::MyType3() = default;

int
main()
{
  // zero intialization
  MyType0 t0{};
  std::cout << t0.x << "\n";

  // Non-trivial type will not zero-initialize its data members
  MyType1 t1{};
  std::cout << t1.x << "\n";

  // zero initialization
  MyType2 t2{};
  std::cout << t2.x << "\n";

  // Non-trivial type will not zero-initialize its data members
  MyType3 t3{};
  std::cout << t3.x << "\n";

  // For const variables
  // Error since it's trivial type
  // const MyType0 ct0;

  // Can initialize with const since it's non-trivial type
  const MyType1 ct1;

  // Error since it's trivial type
  // const MyType2 ct2;

  // Non-trivial type can be intialized with const
  const MyType3 ct3;
}