#include <cassert>
#include <coroutine>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

std::byte
operator""_B(char c)
{
  return static_cast<std::byte>(c);
}

std::byte
operator""_B(unsigned long long c)
{
  return static_cast<std::byte>(c);
}

// Allow multiple bases for awaiter
template<typename T, typename G, typename... Bases>
struct promise_type_base : public Bases...
{
  T mValue;

  auto yield_value(T value)
  {
    mValue = value;
    return std::suspend_always{};
  }

  G get_return_object() { return G{this}; }

  std::suspend_always initial_suspend() { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }
  void return_void() {}
  void unhandled_exception() { std::terminate(); }
};

namespace coro_iterator {
template<typename PT>
struct iterator
{
  using coro_handle = std::coroutine_handle<PT>;

  coro_handle mCoroHdl{nullptr};
  bool mDone{true};

  using RetType = decltype(mCoroHdl.promise().mValue);

  void resume()
  {
    mCoroHdl.resume();
    mDone = mCoroHdl.done();
  }

  iterator() = default;

  iterator(coro_handle hco)
    : mCoroHdl{hco}
  {
    resume();
  }

  iterator& operator++()
  {
    resume();
    return *this;
  }

  bool operator==(iterator const& o) const { return mDone == o.mDone; }

  RetType const& operator*() const { return mCoroHdl.promise().mValue; }
  RetType const* operator->() const { return &(operator*()); }
};
}

template<typename T>
struct awaitable_promise_type_base
{
  std::optional<T> mRecentSignal;

  struct awaiter
  {
    std::optional<T>& mRecentSignal;

    bool await_ready() const { return mRecentSignal.has_value(); }

    void await_suspend(std::coroutine_handle<>) {}

    T await_resume()
    {
      assert(mRecentSignal.has_value());
      auto tmp = *mRecentSignal;
      mRecentSignal.reset();
      return tmp;
    }
  };

  [[nodiscard]] awaiter await_transform(T) { return awaiter{mRecentSignal}; }
};

template<typename T, typename U>
struct [[nodiscard]] async_generator
{
  using promise_type =
    promise_type_base<T, async_generator, awaitable_promise_type_base<U>>;

  using PromiseTypeHandle = std::coroutine_handle<promise_type>;

  T operator()()
  {
    // The move also clears the mValue of the promise
    auto tmp{std::move(mCoroHdl.promise().mValue)};

    // But we have to set it to a defined state
    mCoroHdl.promise().mValue.clear();

    return tmp;
  }

  void SendSignal(U signal)
  {
    mCoroHdl.promise().mRecentSignal = signal;
    if(!mCoroHdl.done()) {
      mCoroHdl.resume();
    }
  }

  async_generator(async_generator const&) = delete;
  async_generator(async_generator&& rhs)
    : mCoroHdl{std::exchange(rhs.mCoroHdl, nullptr)}
  {
  }

  ~async_generator()
  {
    if(mCoroHdl) {
      mCoroHdl.destroy();
    }
  }

private:
  // As the default constructor is private, G needs to be a friend
  friend promise_type;
  explicit async_generator(promise_type* p)
    : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {
  }

  PromiseTypeHandle mCoroHdl;
};

template<typename T>
struct generator
{
  using promise_type = promise_type_base<T, generator>;
  using PromiseTypeHandle = std::coroutine_handle<promise_type>;
  using iterator = coro_iterator::iterator<promise_type>;

  iterator begin() { return {mCoroHdl}; }
  iterator end() { return {}; }

  generator(generator const&) = delete;
  generator(generator&& rhs)
    : mCoroHdl(rhs.mCoroHdl)
  {
    rhs.mCoroHdl = nullptr;
  }

  ~generator()
  {
    if(mCoroHdl) {
      mCoroHdl.destroy();
    }
  }

private:
  // As the default constructor is private, G needs to be a friend
  friend promise_type;
  explicit generator(promise_type* p)
    : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {
  }

  PromiseTypeHandle mCoroHdl;
};

using FSM = async_generator<std::string, std::byte>;

static const std::byte ESC{'H'};
static const std::byte SOF{0x10};

FSM
Parse()
{
  while(true) {
    std::byte b = co_await std::byte{};
    if(ESC != b) {
      continue;
    }
    b = co_await std::byte{};
    if(SOF != b) {
      // A not looking at a start sequence
      continue;
    }

    std::string frame{};
    // capture the full frame
    while(true) {
      b = co_await std::byte{};

      if(ESC == b) {
        // skip this byte and look at the next one
        b = co_await std::byte{};

        if(SOF == b) {
          co_yield frame;
          break;
        } else if(ESC != b) {
          break;
        }
      }
      frame += static_cast<char>(b);
    }
  }
}

generator<std::byte>
sender(std::vector<std::byte> fakeBytes)
{
  for(auto const& b : fakeBytes) {
    co_yield b;
  }
}

void
HandleFrame(std::string const& frame)
{
  std::cout << frame.c_str() << "\n";
}

void
ProcessStream(generator<std::byte>& stream, FSM& parse)
{
  for(auto const& b : stream) {
    // send the new byte to the waiting Parse coroutine
    parse.SendSignal(b);

    // Check whether we have a complete frame
    if(auto const& res = parse(); res.length()) {
      HandleFrame(res);
    }
  }
}

int
main()
{
  std::vector<std::byte> fakeBytes1{
    0x70_B,
    ESC,
    SOF,
    ESC,
    'H'_B,
    'e'_B,
    'l'_B,
    'l'_B,
    'o'_B,
    ESC,
    SOF,
    0x7_B,
    ESC,
    SOF};

  // Simulate the first network stream
  auto stream1 = sender(std::move(fakeBytes1));

  // Create the Parse coroutine and store the handle in p
  auto p = Parse();

  // Process the bytes
  ProcessStream(stream1, p);

  // Simulate the reopening of the network stream
  std::vector<std::byte> fakeBytes2{
    'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B};

  // Simulate a second network stream
  auto stream2 = sender(std::move(fakeBytes2));

  // We still use the former p and feed it with new bytes
  ProcessStream(stream2, p);
}
