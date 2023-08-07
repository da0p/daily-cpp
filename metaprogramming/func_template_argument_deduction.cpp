#include <cstdlib>
#include <iostream>

template<typename T>
void
process(T arg)
{
  std::cout << "process " << arg << "\n";
}

// Types (both cv-qualified and non-qualified) of the form T, T const, T
// volatile
struct account_t
{
  int number;
};

template<typename T>
void
process_1(T)
{
  std::cout << "T\n";
}

template<typename T>
void
process_2(T const)
{
  std::cout << "T const\n";
}

template<typename T>
void
process_3(T volatile)
{
  std::cout << "T volatile\n";
}

// Pointers (T*), l-value references (T&), and r-value references (T&&)
template<typename T>
void
process_4(T*)
{
  std::cout << "T*\n";
}

template<typename T>
void
process_4(T&)
{
  std::cout << "T&\n";
}

template<typename T>
void
process_5(T&&)
{
  std::cout << "T&&\n";
}

// Arrays such as T[5], or C[5][n], where C is a class type and n is a non-type
// template argument
template<typename T>
void
process_6(T[5])
{
  std::cout << "T[5]\n";
}

template<size_t n>
void
process_7(account_t[5][n])
{
  std::cout << "C[5][n]\n";
}

// Pointers to functions, with the form T(*)(), C(*)(T), and T(*)(U), where C
// is a class type and T and U are type template parameters.
template<typename T>
void
process_8(T (*)())
{
  std::cout << "T(*)()\n";
}

template<typename T>
void
process_8(account_t (*)(T))
{
  std::cout << "C (*) (T)\n";
}

template<typename T, typename U>
void
process_8(T (*)(U))
{
  std::cout << "T (*)(U)\n";
}

// Pointers to member functions with one of the following forms, T (C::*)(),
// T(C::*)(U), T (U::*)(), T (U::*)(V), C (T::*)(), C (T::*)(U), and D (C::*)(T)
// where C and D are class types and T, U, and V are type template parameters
struct person_account_t
{
  int number;
  int get_number() { return number; }
  int from_string(std::string text) { return std::atoi(text.c_str()); }
};

struct transaction_t
{
  double amount;
};

struct balance_report_t
{};

struct balance_t
{
  person_account_t account;
  double amount;

  person_account_t get_account() { return account; }
  int get_account_numer() { return account.number; }
  bool can_withdraw(double const value) { return amount >= value; }
  transaction_t withdraw(double const value)
  {
    amount -= value;
    return transaction_t{-value};
  }
  balance_report_t make_report(int const type) { return {}; }
};

template<typename T>
void
process_9(T (person_account_t::*)())
{
  std::cout << "T (C::*)()\n";
}

template<typename T, typename U>
void
process_9(T (person_account_t::*)(U))
{
  std::cout << "T (C::*)(U)\n";
}

template<typename T, typename U>
void
process_9(T (U::*)())
{
  std::cout << "T (U::*)()\n";
}

template<typename T, typename U, typename V>
void
process_9(T (U::*)(V))
{
  std::cout << "T (U::*)(V)\n";
}

template<typename T>
void
process_9(person_account_t (T::*)())
{
  std::cout << "C (T::*)(U)\n";
}

template<typename T, typename U>
void
process_9(transaction_t (T::*)(U))
{
  std::cout << "C (T::*)(U)\n";
}

template<typename T>
void
process_9(balance_report_t (balance_t::*)(T))
{
  std::cout << "D (C::*)(T)\n";
}

// Pointers to data members such as T C::*, C T::*, and T U::*, where C is a
// class type and T and U are type template parameters.
template<typename T>
void
process_10(T person_account_t::*)
{
  std::cout << "T C::*\n";
}

template<typename T>
void
process_10(person_account_t T::*)
{
  std::cout << "C T::*\n";
}

template<typename T, typename U>
void
process_10(T U::*)
{
  std::cout << "T U::*\n";
}

// A template with an argument list that contains at least one type template
// parameter; the general form is C<T>, where C is a class type and T is a type
// template parameter
template<typename T>
struct wrapper
{
  T data;
};

template<typename T>
void
process_11(wrapper<T>)
{
  std::cout << "C<T>\n";
}

// A template with an argument list that contains at least one non-type template
// argument; the general form is C<i>, where C is a class type and i a non-type
// template argument
template<size_t N>
struct int_array
{
  int data[N];
};

template<size_t N>
void
process_12(int_array<N>)
{
  std::cout << "C<N>\n";
}

// A template template argument with an argument list that contains at least
// one type template parameter; the general form is TT<T>, where TT is a
// template template parameter and T is a type template;
template<template<typename> class TT, typename T>
void
process_13(TT<T>)
{
  std::cout << "TT<T>\n";
}

// A template template argument with arugment list that contains at least one
// non-type template argument; the general form is TT<i>, where TT is a template
// template parameter and i is a non-type template argument;
template<template<size_t> typename TT, size_t i>
void
process_14(TT<i>)
{
  std::cout << "TT<i>\n";
}

// A template template argument with an argument list that has no template
// arguments dependent on a template parameter; this has the form TT<C>, where
// TT is the template template parameter and C is a class type
template<template<typename> typename TT>
void
process_15(TT<person_account_t>)
{
  std::cout << "TT<C>\n";
}

// Some limitations
// This is from the book
// The compiler cannot deduce the type of a type template argument, from the
// type of a non-type template argument
// but c++ 20 can do it without any problem!!!!
template<typename T, T i>
void
process(double arr[i])
{
  using index_type = T;
  std::cout << "processing " << i << " doubles"
            << "\n";
  std::cout << "index type is " << typeid(T).name() << "\n";
}

// The compiler is not able to determine the type of a template argument from
// the type of a default value.
template<typename T>
void
process_16(T a = 0, T b = 42)
{
  std::cout << a << ", " << b << "\n";
}

// Although the compiler can deduce function template arguments from pointer
// to functions or pointer to member functions, as we have seen earlier, there
// are a couple of restrictions to this capability: it cannot deduce arguments
// from pointers to function templates, nor from a pointer to a function that
// has an overloaded set with more than one overloaded function matching the
// required type.
template<typename T>
void
invoke(void (*pfun)(T, int))
{
  pfun(T{}, 42);
}

template<typename T>
void
alpha(T, int)
{
  std::cout << "alpha(T, int)"
            << "\n";
}

void
beta(int, int)
{
  std::cout << "beta(int, int)"
            << "\n";
}

void
beta(short, int)
{
  std::cout << "beta(short, int)"
            << "\n";
}

void
gamma(short, int, long long)
{
  std::cout << "gamma(short, int, long long)"
            << "\n";
}

void
gamma(double, int)
{
  std::cout << "gamma(double, int)"
            << "\n";
}

// Another limitation of the compiler is the argument deduction of the primary
// dimension of an array. The reason is this not part of function parameter
// types. The exceptions to this limitation are the cases when the dimension
// refers to a reference or pointer type.
template<size_t Size>
void
process_17(int a[Size])
{
  std::cout << "process(int[Size])"
            << "\n";
}

template<size_t Size>
void
process_18(int a[5][Size])
{
  std::cout << "process(int[5][Size])"
            << "\n";
}

template<size_t Size>
void
process_19(int (&a)[Size])
{
  std::cout << "process(int[Size]&)"
            << "\n";
}

template<size_t Size>
void
process_20(int (*a)[Size])
{
  std::cout << "process(int[Size]*)"
            << "\n";
}

// If a non-type template argument is used in an expression in the function
// template parameter list, thent he compilder cannot deduce its value
template<size_t N>
struct ncube
{
  static constexpr size_t dimensions = N;
};

template<size_t N>
void
process_21(ncube<N - 1> cube)
{
  std::cout << cube.dimensions << "\n";
}

int
main()
{
  // CTAD
  process(42);
  // redundant since compiler can deduce the type automatically
  process<int>(42);
  // T is short, specified explicitly
  process<short>(42);

  account_t ac{42};
  process_1(ac); // T
  process_2(ac); // T const
  process_3(ac); // T volatile

  process_4(&ac); // T*
  process_4(ac);  // T&
  process_5(ac);  // T&&

  account_t arr1[5];
  process_6(arr1); // T[5]

  account_t ac_1{42};
  process_6(&ac_1);

  account_t arr2[5][3];
  process_7(arr2);

  account_t (*pf1)() = nullptr;
  account_t (*pf2)(int) = nullptr;
  account_t (*pf3)(int) = nullptr;

  process_8(pf1); // T(*)()
  process_8(pf2); // C(*)(T)
  process_8(pf3); // T (*)(U)

  int (person_account_t::*pfm1)() = &person_account_t::get_number;
  int (person_account_t::*pfm2)(std::string) = &person_account_t::from_string;

  int (balance_t::*pfm3)() = &balance_t::get_account_numer;
  bool (balance_t::*pfm4)(double) = &balance_t::can_withdraw;
  person_account_t (balance_t::*pfm5)() = &balance_t::get_account;
  transaction_t (balance_t::*pfm6)(double) = &balance_t::withdraw;
  balance_report_t (balance_t::*pfm7)(int) = &balance_t::make_report;

  process_9(pfm1); // T (C::*)()
  process_9(pfm2); // T (C::*)(U)
  process_9(pfm3); // T (U::*)()
  process_9(pfm4); // T (U::*)(V)
  process_9(pfm5); // C (T::*)()
  process_9(pfm6); // C (T::*)(U)
  process_9(pfm7); // D (C::*)(T)

  process_10(&person_account_t::number); // T C::*
  process_10(&balance_t::account);       // C T::*
  process_10(&balance_t::amount);        // T U::*

  wrapper<double> wd{42.0};
  process_11(wd); // C<T>

  int_array<5> ia{};
  process_12(ia); // C<N>

  process_13(wd); // TT<U>

  process_14(ia); // TT<i>

  wrapper<person_account_t> wa{{42}};
  process_15(wa); // TT<C>

  double arr[5]{};

  process(arr);
  process<int, 5>(arr);

  // error
  // process_16();

  // Ok
  process_16<int>();
  // Can be deduced from the passing argument
  process_16(10);

  // error, cannot deduce from function template
  // invoke(&alpha);

  // error, cannot deduce from function with different overloads
  // invoke(&beta);

  // Ok
  invoke(&gamma);

  int arr3[10];
  int arr4[5][10];

  // error, cannot deduce
  // process_17(arr3);
  // but dimension refers to a reference or pointer type
  process_18(arr4);
  process_19(arr3);
  process_20(&arr3);

  ncube<5> cube;
  // error, cannot deduce from expression
  // process_21(cube);

  // Ok
  process_21<6>(cube);

  return EXIT_SUCCESS;
}