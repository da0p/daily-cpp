#include <coroutine>
#include <exception>
#include <iostream>

template<typename T, typename G>
struct promise_type_base
{
  T mValue; // The value yielded or returned from a coroutine

  // Invoked by co_yield or co_return
  auto yield_value(T value)
  {
    // Store the yielded value for access outside the coroutine
    mValue = std::move(value);

    // Suspend the coroutine here
    return std::suspend_always{};
  }

  // Return generator
  G get_return_object() { return G{this}; }

  std::suspend_always initial_suspend() { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }
  void return_void() {}
  void unhandled_exception() { std::terminate(); }
  static auto get_return_object_on_allocation_failure() { return G{nullptr}; }
};

namespace coro_iterator {
template<typename PT>
struct iterator
{
  std::coroutine_handle<PT> mCoroHdl{nullptr};

  void resume()
  {
    if(!mCoroHdl.done()) {
      mCoroHdl.resume();
    }
  }

  iterator() = default;
  iterator(std::coroutine_handle<PT> hco)
    : mCoroHdl{hco}
  {
    resume();
  }

  void operator++() { resume(); }
  bool operator==(iterator const&) const { return mCoroHdl.done(); }

  auto const& operator*() const { return mCoroHdl.promise().mValue; }
};
};

template<typename T>
struct generator
{
  using promise_type = promise_type_base<T, generator>;
  using PromiseTypeHandle = std::coroutine_handle<promise_type>;

  // Make the generator iterable
  using iterator = coro_iterator::iterator<promise_type>;
  iterator begin() { return {mCoroHdl}; }
  iterator end() { return {}; }

private:
  // As the default constructor is private, promise_type needs to be a friend
  friend promise_type;

  explicit generator(promise_type* p)
    : mCoroHdl{PromiseTypeHandle::from_promise(*p)}
  {
  }

  // The coroutine handle
  PromiseTypeHandle mCoroHdl;
};

using IntGenerator = generator<int>;

void
UseCounterValue(int i);

// Return a coroutine object
IntGenerator
counter(int start, int end)
{
  while(start < end) {
    // Yielding a value and giving control back to the caller
    co_yield start;
    ++start;
  }
}

void
UseCounter()
{
  auto g = counter(1, 5);

  // This sequence runs from 1 to 5
  for(auto i : g) {
    UseCounterValue(i);
  }
}

void
UseCounterValue(int i)
{
  std::cout << i << "\n";
}

int
main()
{
  UseCounter();
}