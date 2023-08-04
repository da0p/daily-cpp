#include <iostream>

template<typename T, int S>
struct collection
{
  void operator()() { std::cout << "primary template\n"; }
};

template<typename T>
struct collection<T, 10>
{
  void operator()() { std::cout << "partial specialization <T, 10>\n"; }
};

template<int S>
struct collection<int, S>
{
  void operator()() { std::cout << "partial specialization <int, S>\n"; }
};

template<typename T, int S>
struct collection<T*, S>
{
  void operator()() { std::cout << "partial specialization <T*, S>\n"; }
};

int
main(int argc, char* argv[])
{
  collection<char, 42> a; // primary template
  collection<int, 42> b;  // partial specialization <int, S>
  collection<char, 10> c; // partial specialization <T, 10>
  collection<int*, 20> d; // partial specialization <T*, S>

  // collection<int, 10> e;   // error: collection<T, 10> or collection<int, S>
  // collection<char*, 10> f; // error: collection<T, 10> or collection<T*, S>
}