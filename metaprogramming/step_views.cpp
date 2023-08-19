#include <iostream>
#include <ranges>
#include <vector>

template<typename R>
struct step_iterator;

template<typename R>
struct step_sentinel
{
  using base = std::ranges::iterator_t<R>;
  using size_type = std::ranges::range_difference_t<R>;

  step_sentinel() = default;

  constexpr step_sentinel(base end)
    : end_{end}
  {
  }

  constexpr bool is_at_end(step_iterator<R> it) const;

private:
  base end_;
};

template<typename R>
constexpr bool
step_sentinel<R>::is_at_end(step_iterator<R> it) const
{
  return end_ == it.value();
}

template<typename R>
struct step_iterator : std::ranges::iterator_t<R>
{
  using base = std::ranges::iterator_t<R>;
  using value_type = typename std::ranges::range_value_t<R>;
  using reference_type = typename std::ranges::range_reference_t<R>;

  constexpr step_iterator(
    base start,
    base end,
    std::ranges::range_difference_t<R> step
  )
    : pos_{start}
    , end_{end}
    , step_{step}
  {
  }

  constexpr step_iterator operator++(int)
  {
    auto ret = *this;
    pos_ = std::ranges::next(pos_, step_, end_);
    return ret;
  }

  constexpr step_iterator& operator++()
  {
    pos_ = std::ranges::next(pos_, step_, end_);
    return *this;
  }

  constexpr reference_type operator*() const { return *pos_; }

  constexpr bool operator==(step_sentinel<R> s) const
  {
    return s.is_at_end(*this);
  }

  constexpr base const value() const { return pos_; }

private:
  base pos_;
  base end_;
  std::ranges::range_difference_t<R> step_;
};

namespace details {
using test_range_t = std::ranges::views::all_t<std::vector<int>>;
static_assert(std::input_iterator<step_iterator<test_range_t>>);
static_assert(std ::sentinel_for<
              step_sentinel<test_range_t>,
              step_iterator<test_range_t>>);
}

/**
 * There is a pattern that must be followed when defining a range adaptor. This
 * pattern is represented by the following aspects:
 *
 * - The class template must have a template argument that mees the
 *   std::ranges::view concept.
 * - The class tempalte should be derived from std::ranges::view_interface. This
 *   takes a template argument itself and that should be the range adaptor
 *   class. This is basically an implementation of the CRTP.
 * - The class must have a default constructor.
 * - The class must have a base member function that returns the underlying
 *   range.
 * - The class must have a begin member function that returns an iterator to
 *   the first element in the range.
 * - The clas must have an end member function that return either an iterator to
 *   the one-past-the-last-element of the range or a sentinel.
 * - For ranges that meet the requirements of the std::ranges::sized_range
 *   concept, this class must also contain a member function called size that
 *   returns the number of elements in the range.
 *
 */
template<std::ranges::view R>
struct step_view : public std::ranges::view_interface<step_view<R>>
{
private:
  R base_;
  std::ranges::range_difference_t<R> step_;

public:
  step_view() = default;
  constexpr step_view(R base, std::ranges::range_difference_t<R> step)
    : base_(std::move(base))
    , step_(step)
  {
  }

  constexpr R base() const&
    requires std::copy_constructible<R>
  {
    return base_;
  }

  constexpr R base() && { return std::move(base_); }

  constexpr std::ranges::range_difference_t<R> const& increment() const
  {
    return step_;
  }

  constexpr auto begin()
  {
    return step_iterator<R const>(
      std::ranges::begin(base_), std::ranges::end(base_), step_
    );
  }

  constexpr auto begin() const
    requires std::ranges::range<R const>
  {
    return step_iterator<R const>(
      std::ranges::begin(base_), std::ranges::end(base_), step_
    );
  }

  constexpr auto end()
  {
    return step_sentinel<R const>{std::ranges::end(base_)};
  }

  constexpr auto size() const
    requires std::ranges::sized_range<R const>
  {
    auto d = std::ranges::size(base_);
    return step_ == 1 ? d : static_cast<int>((d + 1) / step_);
  }

  constexpr auto size()
    requires std::ranges::sized_range<R const>
  {
    auto d = std::ranges::size(base_);
    return step_ == 1 ? d : static_cast<int>((d + 1) / step_);
  }
};

// This template deduction guide is needed in order to make it possible to use
// class template argument deduction.
template<typename R>
step_view(R&& base, std::ranges::range_difference_t<R> step)
  -> step_view<std::ranges::views::all_t<R>>;

namespace details {
struct step_view_fn_closure
{
  std::size_t step_;
  constexpr step_view_fn_closure(std::size_t step)
    : step_(step)
  {
  }

  template<std::ranges::range R>
  constexpr auto operator()(R&& r) const
  {
    return step_view(std::forward<R>(r), step_);
  }
};

template<std::ranges::range R>
constexpr auto
operator|(R&& r, step_view_fn_closure&& a)
{
  return std::forward<step_view_fn_closure>(a)(std::forward<R>(r));
}

struct step_view_fn
{
  template<std::ranges::range R>
  constexpr auto operator()(R&& r, std::size_t step) const
  {
    return step_view(std::forward<R>(r), step);
  }

  constexpr auto operator()(std::size_t step) const
  {
    return step_view_fn_closure(step);
  }
};
}

namespace views {
inline constexpr details::step_view_fn step;
}

int
main()
{
  for(auto i : std::views::iota(1, 10) | views::step(1)) {
    std::cout << i << "\n";
  }

  for(auto i : std::views::iota(1, 10) | views::step(2)) {
    std::cout << i << "\n";
  }

  for(auto i : std::views::iota(1, 10) | views::step(3)) {
    std::cout << i << "\n";
  }

  for(auto i : std::views::iota(1, 10) | views::step(2) | std::views::take(3)) {
    std::cout << i << "\n";
  }
}