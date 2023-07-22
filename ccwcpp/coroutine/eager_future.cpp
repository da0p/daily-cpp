#include <coroutine>
#include <iostream>
#include <memory>

template<typename T>
struct MyFuture
{
  std::shared_ptr<T> value;
  MyFuture(std::shared_ptr<T> p)
    : value(p)
  {
  }

  ~MyFuture() {}

  T get() { return *value; }

  struct promise_type
  {
    std::shared_ptr<T> ptr = std::make_shared<T>();
    ~promise_type() {}
    MyFuture<T> get_return_object()
    {
      std::cout << "Get return object"
                << "\n";

      return ptr;
    }

    void return_value(T v)
    {
      std::cout << "Return value"
                << "\n";
      *ptr = v;
    }

    std::suspend_never initial_suspend()
    {
      std::cout << "Initial suspend"
                << "\n";
      return {};
    }

    std::suspend_never final_suspend() noexcept
    {
      std::cout << "Final suspend"
                << "\n";

      return {};
    }

    void unhandled_exception() { std::exit(1); }
  };
};

MyFuture<int>
createFuture()
{
  co_return 2021;
}

int
main(int argc, char* argv[])
{
  auto fut = createFuture();

  std::cout << "fut.get(): " << fut.get() << "\n\n";
}
