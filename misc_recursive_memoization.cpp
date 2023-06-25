#include <iostream>
#include <map>
#include <mutex>
#include <tuple>
#include <type_traits>
#include <unordered_map>

namespace detail {

class null_param
{};

template<class Sig, class F>
class memoize_helper;

template<class Result, class... Args, class F>
class memoize_helper<Result(Args...), F>
{
private:
  using function_type = F;
  using args_tuple_type = std::tuple<std::decay_t<Args>...>;

  function_type f;

  // Defines the cache, and, because it's mutable, synchronizes all the changes
  mutable std::map<args_tuple_type, Result> m_cache;
  mutable std::recursive_mutex m_cache_mutex;

public:
  // The constructors need to initialize the wrapped function.
  // You could make copy-constructor copy the cached values as well,
  // but that's not necessary.

  template<typename Function>
  memoize_helper(Function&& f, null_param)
    : f(f)
  {
  }

  memoize_helper(memoize_helper const& other)
    : f(other.f)
  {
  }

  template<class... InnerArgs>
  Result operator()(InnerArgs&&... args) const
  {
    std::unique_lock<std::recursive_mutex> lock{m_cache_mutex};

    // Searches for the cached value
    auto const args_tuple = std::make_tuple(args...);
    auto const cached = m_cache.find(args_tuple);

    // if the cached value is found, return it without calling f
    if(cached != m_cache.end()) {
      return cached->second;
    } else {
      // if the cached value isn't found, call f and store the result. Pass
      // *this as the first argument: the function to be ued for the recursive
      // call.
      auto&& result = f(*this, std::forward<InnerArgs>(args)...);
      m_cache[args_tuple] = result;
      return result;
    }
  }
};
}

using detail::memoize_helper;

template<class Sig, class F>
memoize_helper<Sig, std::decay_t<F>>
make_memoized_r(F&& f)
{
  return {std::forward<F>(f), detail::null_param{}};
}

int
main(int argc, char* argv[])
{
  auto fib_memo =
    make_memoized_r<unsigned int(unsigned int)>([](auto& fib, unsigned int n) {
      std::cout << "Calculating " << n << "!\n";
      return n == 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
    });

  std::cout << "1st Calc: Fib(15) = " << fib_memo(15) << std::endl;
  std::cout << "2nd Calc: Fib(15) = " << fib_memo(15) << std::endl;
}