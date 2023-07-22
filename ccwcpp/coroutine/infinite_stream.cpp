#include <coroutine>
#include <iostream>
#include <memory>

template<typename T>
struct Generator
{
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  handle_type coro;

  Generator(handle_type h)
    : coro(h)
  {
  }

  ~Generator()
  {
    if(coro) {
      coro.destroy();
    }
  }

  Generator(Generator const&) = delete;
  Generator& operator=(Generator const&) = delete;
  Generator(Generator&& oth) noexcept
    : coro(oth.coro)
  {
    oth.coro = nullptr;
  }
  Generator& operator=(Generator&& oth) noexcept
  {
    coro = oth.coro;
    oth.coro = nullptr;
    return *this;
  }
  T getValue() { return coro.promise().current_value; }
  bool next()
  {
    coro.resume();
    return !coro.done();
  }

  struct promise_type
  {
    promise_type() = default;

    ~promise_type() = default;

    auto initial_suspend()
    {
      std::cout << "initial_suspend\n\n";
      return std::suspend_always{};
    }
    auto final_suspend() noexcept
    {
      std::cout << "final_suspend\n\n";
      return std::suspend_always{};
    }
    auto get_return_object()
    {
      std::cout << "get_return_object\n\n";
      return Generator{handle_type::from_promise(*this)};
    }
    auto return_void()
    {
      std::cout << "return_void\n\n";
      return std::suspend_never{};
    }
    auto yield_value(const T value)
    {
      std::cout << "yield_value\n";
      current_value = value;
      return std::suspend_always{};
    }
    void unhandled_exception() { std::exit(1); }
    T current_value;
  };
};

Generator<int>
getNext(int start = 0, int step = 1)
{
  auto value = start;
  while(true) {
    co_yield value;
    value += step;
  }
}

int
main(int argc, char* argv[])
{
  std::cout << "getNext(): ";
  auto gen = getNext();
  for(int i = 0; i <= 10; ++i) {
    gen.next();
    std::cout << " " << gen.getValue();
  }
  std::cout << "\n\n";
  std::cout << "getNext(100, -10):";
  auto gen_2 = getNext(100, -10);
  for(int i = 0; i <= 20; ++i) {
    gen_2.next();
    std::cout << " " << gen_2.getValue() << "\n\n";
  }
}