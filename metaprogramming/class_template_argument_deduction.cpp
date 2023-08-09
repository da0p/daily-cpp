#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T, typename... Ts, typename Allocator = std::allocator<T>>
auto
make_vector(T&& first, Ts&&... args)
{
  return std::vector<std::decay_t<T>, Allocator>{
    std::forward<T>(first), std::forward<Ts>(args)...};
}

template<typename... Args>
void
make_print(Args... args)
{
  ((std::cout << args << " "), ...);
}

template<typename T>
struct point_t
{
  point_t(T vx, T vy)
    : x(vx)
    , y(vy)
  {
  }

private:
  T x;
  T y;
};

template<typename T>
struct range_t
{
  // This deduction guide is instructing is that when a call to the constructor
  // with two iterator arguments is encountered, the value of the template
  // parameter T should be deduced to be the value type of the iterator traits
  template<typename Iter>
  range_t(Iter first, Iter last)
  {
    std::copy(first, last, std::back_inserter(data));
  }

private:
  std::vector<T> data;
};

int
main()
{
  auto v = make_vector(1, 2, 3, 4, 5);
  make_print(v[0], v[1], v[2], v[3], v[4]);

  auto p = new point_t(1, 2);

  int arr[] = {1, 2, 3, 4, 5};
  range_t<int> r(std::begin(arr), std::end(arr));

  return EXIT_SUCCESS;
}