#include <initializer_list>
#include <iostream>
#include <vector>

/**
 * Expression templates are a metaprogramming technique that enables lazy
 * evaluation of a compuation at compile-time. This helps to avoid inefficient
 * operations that occur at runtime.
 *
 * Disadvantages:
 * - Comes with more codes, cubersome to read or understand
 *
 */

template<typename T, typename C = std::vector<T>>
struct vector
{
  vector() = default;

  vector(std::size_t const n)
    : data_(n)
  {
  }

  vector(std::initializer_list<T>&& l)
    : data_(l)
  {
  }

  vector(C const& other)
    : data_(other)
  {
  }

  template<typename U, typename X>
  vector(vector<U, X> const& other)
    : data_(other.size())
  {
    for(std::size_t i = 0; i < other.size(); ++i) {
      data_[i] = static_cast<T>(other[i]);
    }
  }

  template<typename U, typename X>
  vector& operator=(vector<U, X> const& other)
  {
    data_.resize(other.size());
    for(std::size_t i = 0; i < other.size(); ++i) {
      data_[i] = static_cast<T>(other[i]);
    }
    return *this;
  }

  std::size_t size() const noexcept { return data_.size(); }

  T operator[](const std::size_t i) const { return data_[i]; }

  T& operator[](const std::size_t i) { return data_[i]; }

  C& data() noexcept { return data_; }

  C const& data() const noexcept { return data_; }

private:
  C data_;
};

template<typename L, typename R>
struct vector_add
{
  vector_add(L const& a, R const& b)
    : lhv(a)
    , rhv(b)
  {
  }

  auto operator[](std::size_t const i) const { return lhv[i] + rhv[i]; }

  std::size_t size() const noexcept { return lhv.size(); }

private:
  L const& lhv;
  R const& rhv;
};

template<typename L, typename R>
struct vector_mul
{
  vector_mul(L const& a, R const& b)
    : lhv(a)
    , rhv(b)
  {
  }

  auto operator[](std::size_t const i) const { return lhv[i] * rhv[i]; }

  std::size_t size() const noexcept { return lhv.size(); }

private:
  L const& lhv;
  R const& rhv;
};

template<typename S, typename R>
struct vector_scalar_mul
{
  vector_scalar_mul(S const& a, R const& b)
    : scalar(a)
    , rhv(b)
  {
  }

  auto operator[](std::size_t const i) const { return scalar * rhv[i]; }

  std::size_t size() const noexcept { return rhv.size(); }

private:
  S const& scalar;
  R const& rhv;
};

template<typename T, typename L, typename U, typename R>
auto
operator+(vector<T, L> const& a, vector<U, R> const& b)
{
  using result_type = decltype(std::declval<T>() + std::declval<U>());
  return vector<result_type, vector_add<L, R>>(
    vector_add<L, R>(a.data(), b.data())
  );
}

template<typename T, typename L, typename U, typename R>
auto
operator*(vector<T, L> const& a, vector<U, R> const& b)
{
  using result_type = decltype(std::declval<T>() * std::declval<U>());
  return vector<result_type, vector_mul<L, R>>(
    vector_mul<L, R>(a.data(), b.data())
  );
}

template<typename T, typename S, typename R>
auto
operator*(S const& s, vector<T, R> const& v)
{
  using result_type = decltype(std::declval<T>() * std::declval<S>());
  return vector<result_type, vector_scalar_mul<S, R>>(
    vector_scalar_mul<S, R>(s, v.data())
  );
}

int
main()
{
  vector<int> v1{1, 2, 3};
  vector<int> v2{4, 5, 6};
  double a{1.5};

  vector<double> v3 = v1 + a * v2;
  vector<int> v4 = v1 * v2 + v1 * v2;
}