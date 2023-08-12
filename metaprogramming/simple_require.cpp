#include <concepts>
#include <cstdlib>
#include <iostream>

template<typename T>
concept arithmetic = requires { std::is_arithmetic_v<T>; };

template<typename T>
concept addable = requires(T a, T b) { a + b; };

template<typename T>
concept logger = requires(T t) {
  t.error("just");
  t.warning("a");
  t.info("demo");
};

template<logger T>
void
log_error(T& logger)
{
}

struct console_logger
{
  void error(std::string_view text) {}
  void warning(std::string_view text) {}
  void info(std::string_view text) {}
};

struct stream_logger
{
  void error(std::string_view text, bool = false) {}
  void warning(std::string_view text, bool = false) {}
  void info(std::string_view text, bool) {}
};

int
main()
{
  console_logger cl;
  log_error(cl);

  stream_logger sl;
  // Error, does not satisty requirement
  // log_error(sl);

  return EXIT_SUCCESS;
}