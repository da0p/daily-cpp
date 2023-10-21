#include <chrono>
#include <format>
#include <iostream>

enum LogLevel
{
  Info,
  Warning,
  Error
};

template<>
struct std::formatter<LogLevel> : std::formatter<char const*>
{
  inline static char const* LEVEL_NAMES[] = {"Info", "Warning", "Error"};

  auto format(LogLevel c, std::format_context& ctx) const
  {
    return std::formatter<char const*>::format(LEVEL_NAMES[c], ctx);
  }
};

void
vlog(LogLevel level, std::string_view fmt, std::format_args&& args)
{
  auto const now = std::chrono::system_clock::now();
  std::cout << std::format("[{:%Y-%m-%d-%H:%M:%S}]", now)
            << std::format("{}: ", level) << std::vformat(fmt, args) << "\n";
}

constexpr void
log(LogLevel level, std::string_view fmt, auto const&... args)
{
  vlog(level, fmt, std::make_format_args(args...));
}

void
use()
{
  const std::string share{"Amazon"};
  double const price{3'117.02};
  log(LogLevel::Info, "Share price {} very high: {}", share, price);

  errno = 4;
  log(LogLevel::Error, "Unknown stock, errno: {}", errno);
}

int
main()
{
  use();

  return 0;
}