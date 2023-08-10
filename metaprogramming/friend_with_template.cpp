#include <cstdlib>
#include <iostream>

struct wrapper;

template<typename T>
void
print_spec(wrapper const& w);

struct wrapper
{
  wrapper(int const v)
    : value(v)
  {
  }

private:
  int value;

  template<typename T>
  friend void print(wrapper const&);

  // This specialization only allows int version of this function to access
  // private member of this class
  friend void print_spec<int>(wrapper const&);

  template<typename T>
  friend struct printer;
};

template<typename T>
void
print(wrapper const& w)
{
  std::cout << w.value << "\n";
}

template<>
void
print_spec<int>(wrapper const& w)
{
  std::cout << "print_spec: w.value = " << w.value << "\n";
}

template<typename T>
struct printer
{
  void operator()(wrapper const& w) { std::cout << w.value << "\n"; }
};

template<typename T>
struct printer_2;

template<typename T>
struct wrapper_2;

template<typename T>
void
print_4(wrapper_2<T> const&);

template<typename T>
struct wrapper_2
{
  wrapper_2(T const v)
    : value(v)
  {
  }

private:
  T value;

  template<typename U>
  friend void print_2(wrapper_2<U> const&);

  template<typename U>
  friend struct printer_2;

  friend void print_4<int>(wrapper_2<int> const&);

  friend struct printer_2<T>;
};

template<typename T>
void
print_2(wrapper_2<T> const& w)
{
  std::cout << w.value << "\n";
}

template<typename T>
struct printer_2
{
  void operator()(wrapper_2<T> const& w) { std::cout << w.value << "\n"; }
};

template<>
void
print_4(wrapper_2<int> const& w)
{
  std::cout << w.value << "\n";
}

int
main()
{
  wrapper w{42};
  print<int>(w);
  print<char>(w);
  print_spec<int>(w);
  // print_spec<double>(w); --> ERROR
  printer<int>()(w);
  printer<double>()(w);

  return EXIT_SUCCESS;
}
