#include <iostream>

template<typename T>
struct parser
{
  // unqualified name found in the current instantiation
  parser* p1;
  // unqualified name found in the current instantiation
  parser<T>* p2;
  // qualified name found in the current instantiation
  ::parser<T>* p3;
  // unqualified name not found in the current instantiation -> not CI
  parser<T*> p4;

  struct token
  {
    // unqualified name found in the CI
    token* t1;
    // qualified name found in the CI
    parser<T>::token* t2;
    // qualified name, qualifier is not found in CI
    typename parser<T*>::token* t3;
  };
};

template<typename T>
struct parser<T*>
{
  // parser<T*> is the CI
  parser<T*>* p1;

  // parser<T> is not the CI
  parser<T>* p2;
};

int
main()
{
  parser<int> parser;
}