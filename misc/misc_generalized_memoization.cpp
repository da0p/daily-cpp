#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>

template<typename Result, typename... Args>
auto
make_memoized(Result (*f)(Args...))
{
  std::map<std::tuple<Args...>, Result> cache;

  return [f, cache](Args... args) mutable -> Result {
    // lambda that gets the arguments and checks whether the result is already
    // cached
    const auto args_tuple = std::make_tuple(args...);
    const auto cached = cache.find(args_tuple);

    if(cached == cache.end()) {
      // in case of a cache miss, calls the function and stores the result
      // to the cache
      auto result = f(args...);
      cache[args_tuple] = result;
      return result;
    } else {
      // if the result is found in the case, returns it to the caller
      return cached->second;
    }
  };
}

unsigned int
fib(unsigned int n)
{
  std::cout << "Calculating " << n << "!\n";
  return n == 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}

int
main(int argc, char* argv[])
{
  auto fib_memo = make_memoized(fib);

  std::cout << "1st time: Fib(15) = " << fib_memo(15) << std::endl;

  std::cout << "2nd time: Fib(15) = " << fib_memo(15) << std::endl;

  return 0;
}