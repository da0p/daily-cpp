#include <concepts>
#include <cstdlib>
#include <iostream>

/**
 * Example 1: Non-throwing concept
 *
 */
template<typename T>
void
f(T) noexcept
{
}

template<typename T>
void
g(T)
{
}

template<typename F, typename... T>
concept NonThrowing = requires(F&& func, T... t) {
  {
    func(t...)
  } noexcept;
};

template<typename F, typename... T>
  requires NonThrowing<F, T...>
void
invoke(F&& func, T... t)
{
  func(t...);
}

/**
 * Timer concept
 *
 */
template<typename T>
concept timer = requires(T t) {
  {
    t.start()
  } -> std::same_as<void>;
  {
    t.stop()
  } -> std::convertible_to<long long>;
};

struct timerA
{
  void start() {}
  long long stop() { return 0; }
};

struct timerB
{
  void start() {}
  int stop() { return 0; }
};

struct timerC
{
  void start() {}
  void stop() {}
  long long getTicks() { return 0; }
};

int
main()
{
  invoke(f<int>, 42);
  // error
  // invoke(g<int>, 42);

  static_assert(timer<timerA>);
  static_assert(timer<timerB>);
  static_assert(!timer<timerC>);

  return EXIT_SUCCESS;
}