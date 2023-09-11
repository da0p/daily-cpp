#include <algorithm>
#include <iostream>

struct X
{
  static int copy_cnt;
  X(int v)
    : mValue(v)
  {
  }

  X(X const& other)
    : mValue(other.mValue)
  {
    ++copy_cnt;
  }

  int mValue;
  friend auto operator<=>(X const&, X const&) = default;
};

int X::copy_cnt = 0;

int
main()
{
  // For functions tht accept an std::initializer_list, it is worth keeping in
  // mind that std::initializer_list is constructed by copy; its internal array
  // elements is copy constructed from the listed elements. Therefore we need
  // to be careful when using std::initializer_list outside of compile-time
  // contexts.
  //
  // In this case, using std::initializer_list leads to 6 copies
  // 5 for result from passing in the variables a to e
  // one is the result of the return from std::max
  X a{1}, b{2}, c{3}, d{4}, e{5};
  auto max = std::max({a, b, c, d, e});
  std::cout << "copy_cnt = " << X::copy_cnt << "\n";
}