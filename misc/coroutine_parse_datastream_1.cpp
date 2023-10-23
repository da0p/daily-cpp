#include <cassert>
#include <coroutine>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using std::byte;
std::byte
operator""_B(char c)
{
  return static_cast<byte>(c);
}

std::byte
operator""_B(unsigned long long c)
{
  return static_cast<byte>(c);
}

template<typename T, typename G, bool InitialSuspend>
struct promise_type_base
{
  T mValue;

  std::suspend_always yield_value(T value)
  {
    mValue = value;
    return {};
  }

  auto initial_suspend()
  {
    // Either suspend always or never
    if constexpr(InitialSuspend) {
      return std::suspend_always{};
    } else {
      return std::suspend_never{};
    }
  }

  std::suspend_always final_suspend() noexcept { return {}; }
  G get_return_object() { return G{this}; }
  void unhandled_exception(){};
  void return_void() {}
};

namespace coro_iterator {
template<typename PT>
struct iterator
{
  using coro_handle = std::coroutine_handle<PT>;

  coro_handle mCoroHdl{};

  using RetType = decltype(mCoroHdl.promise().mValue);

  void resume() { mCoroHdl.resume(); }

  iterator() = default;

  iterator(coro_handle hco)
    : mCoroHdl{hco}
  {
    resume();
  }

  void operator++() { resume(); }

  bool operator==(iterator const&) const { return mCoroHdl.done(); }

  RetType const& operator*() const { return mCoroHdl.promise().mValue; }
};
}

template<typename T, bool InitialSuspend = true>
struct generator
{
  using promise_type = promise_type_base<T, generator, InitialSuspend>;

  using PromiseTypeHandle = std::coroutine_handle<promise_type>;
  using iterator = coro_iterator::iterator<promise_type>;

  iterator begin() { return {mCoroHdl}; }
  iterator end() { return {}; }

  generator(generator const&) = delete;
  generator(generator&& rhs)
    : mCoroHdl{std::exchange(rhs.mCoroHdl, nullptr)}
  {
  }

  ~generator()
  {
    if(mCoroHdl) {
      mCoroHdl.destroy();
    }
  }

  T operator()()
  {
    T tmp{};
    // Use swap for a potential move and defined cleared state
    std::swap(tmp, mCoroHdl.promise().mValue);

    return tmp;
  }

private:
  // The default constructor is private, G needs to be a friend
  friend promise_type;
  explicit generator(promise_type* p)
    : mCoroHdl(PromiseTypeHandle::from_promise(*p))
  {
  }

protected:
  PromiseTypeHandle mCoroHdl;
};

// Awaitable
class DataStreamReader
{
public:
  DataStreamReader() = default;

  // Disable copy and move operations
  DataStreamReader& operator=(DataStreamReader&&) noexcept = delete;

  // Awaiter implementation
  struct Awaiter
  {
    Awaiter& operator=(Awaiter&&) noexcept = delete;
    Awaiter(DataStreamReader& event) noexcept
      : mEvent{event}
    {
      mEvent.mAwaiter = this;
    }

    bool await_ready() const noexcept { return mEvent.mData.has_value(); }

    void await_suspend(std::coroutine_handle<> coroHdl) noexcept
    {
      // Stash the handle of the awaiting coroutine.
      mCoroHdl = coroHdl;
    }

    byte await_resume() noexcept
    {
      assert(mEvent.mData.has_value());
      return *std::exchange(mEvent.mData, std::nullopt);
    }

    void resume() { mCoroHdl.resume(); }

  private:
    DataStreamReader& mEvent;
    std::coroutine_handle<> mCoroHdl{};
  };

  // Make DataStreamReader awaitable
  auto operator co_await() noexcept { return Awaiter{*this}; }

  void set(byte b)
  {
    mData.emplace(b);
    if(mAwaiter) {
      mAwaiter->resume();
    }
  }

private:
  friend struct Awaiter;
  Awaiter* mAwaiter{};
  std::optional<byte> mData{};
};

using FSM = generator<std::string, false>;

static const byte ESC{'H'};
static const byte SOF{0x10};

// pass the stream as a parameter
FSM
Parse(DataStreamReader& stream)
{
  while(true) {
    // await on the stream
    byte b = co_await stream;
    if(ESC != b) {
      continue;
    }

    b = co_await stream;
    // Not looking at a end or start sequence
    if(SOF != b) {
      continue;
    }

    std::string frame{};
    // Capture the full frame
    while(true) {
      b = co_await stream;

      if(ESC == b) {
        // skip this byte and look at the next one
        b = co_await stream;

        if(SOF == b) {
          co_yield frame;
          break;
        } else if(ESC != b) {
          // out of sync
          break;
        }
      }

      frame += static_cast<char>(b);
    }
  }
}

generator<byte>
sender(std::vector<byte> fakeBytes)
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

int
main()
{
  std::vector<byte> fakeBytes1{
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

  std::vector<byte> fakeBytes2{
    'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B};

  auto stream1 = sender(std::move(fakeBytes1));

  // create a datastream reader Awaitable
  DataStreamReader dr{};

  // create the Parse coroutine and pass the DataStreamReader
  auto p = Parse(dr);

  for(auto const& b : stream1) {
    // Send the new byte to the waiting DataStreamReader
    dr.set(b);

    if(auto const& res = p(); res.length()) {
      HandleFrame(res);
    }
  }

  // simulate a second network stream
  auto stream2 = sender(std::move(fakeBytes2));
  for(auto const& b : stream2) {
    dr.set(b);

    if(auto const& res = p(); res.length()) {
      HandleFrame(res);
    }
  }
}