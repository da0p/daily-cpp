#include <array>
#include <iostream>
#include <memory>

struct S
{
  int zero{};     // fine, value initialization
  int a = 10;     // fine, copy initialization
  double b{10.5}; // fine, direct list initialization
  // short c (100); // error, direct initialization with parens
  int d{zero + a}; // dependency, risky, but fine
  // double e {*mem * 2.0}; // undefined!
  int* mem = new int(d);
  std::unique_ptr<int[]> pInts = std::make_unique<int[]>(10);
  long arr[4] = {0, 1, 2, 3};
  std::array<int, 4> moreNumbers{10, 20, 30, 40};
  // long arr2[] = {1, 2}; // cannot deduce
  // auto f = 1;  // error, type deduction doesn't work
  double g{compute()};
  // int& ref{}; // error, cannot set ref to null!
  int& refOk{zero};

  ~S() { delete mem; }
  double compute() { return a * b; }
};

int
initA()
{
  std::cout << "initA() called\n";
  return 1;
}

std::string
initB()
{
  std::cout << "initB() called\n";
  return "World";
}

struct SimpleType
{
  int a{initA()};
  std::string b{initB()};

  SimpleType() {}
  explicit SimpleType(std::string s)
    : b(std::move(s))
  {
  }

  // This copy ctor initialize the fields in the body will trigger default
  // initialization of member variables
  /*
  SimpleType(SimpleType const& other)
  {
    std::cout << "copy ctor\n";
    a = other.a;
    b = other.b;
  }
  */

  // It's better to use initializer list for copy ctor because it will avoid
  // default initialization of member variables
  SimpleType(SimpleType const& other)
    : a(other.a)
    , b(other.b)
  {
    std::cout << "copy ctor\n";
  }

  // Same thing happens as with copy ctor if not using initializer list, default
  // value initialization will kick in
  /*
  SimpleType(SimpleType&& other)
  {
    std::cout << "move ctor\n";
    a = std::move(other.a);
    b = std::move(other.b);
  }
  */
  SimpleType(SimpleType&& other)
    : a(std::move(other.a))
    , b(std::move(other.b))
  {
    std::cout << "move ctor\n";
  }
};

void
showProperties(std::string_view text, S const& s)
{
  std::cout << text << "\n";
  std::cout << ".zero:      " << s.zero << "\n";
  std::cout << ".a:         " << s.a << "\n";
  std::cout << ".b:         " << s.b << "\n";
  std::cout << ".d:         " << s.d << "\n";
  std::cout << "*.mem:      " << s.arr[0] << "\n";
  std::cout << "g:          " << s.g << "\n";
}

int
main()
{
  S s; // default initialization
  showProperties("s", s);

  // aggregate initialization with only the first argument, so it will only set
  // the S::zero data member
  S y{1};
  showProperties("y", y);

  // copy ctor and nsdmi
  SimpleType t1;
  std::cout << "SimpleType t2 = t1:\n";
  SimpleType t2 = t1;

  std::cout << "SimpleType t3 = std::move(t1)\n";
  SimpleType t3 = std::move(t1);

  return 0;
}