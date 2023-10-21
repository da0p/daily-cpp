#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>

class fib_cache
{
public:
  fib_cache()
    : m_previous{0}
    , m_last{1}
    , m_size{2}
  {
  }

  uint64_t size() const { return m_size; }

  std::optional<uint64_t> operator[](uint64_t n) const
  {
    return n == m_size - 1   ? std::optional<uint64_t>(m_last)
           : n == m_size - 2 ? std::optional<uint64_t>(m_previous)
                             : std::nullopt;
  }

  void push_back(unsigned int value)
  {
    m_size++;
    m_previous = m_last;
    m_last = value;
  }

private:
  uint64_t m_previous;
  uint64_t m_last;
  uint64_t m_size;
};

uint64_t
calc_fib(uint64_t n, fib_cache& fibCache)
{
  if(fibCache[n].has_value()) {
    return fibCache[n].value();
  }

  auto cacheResult = calc_fib(n - 1, fibCache) + calc_fib(n - 2, fibCache);
  fibCache.push_back(cacheResult);

  return cacheResult;
}

std::optional<unsigned int>
parse_arg(std::string const& arg)
{
  try {
    auto convertedInt = std::stoi(arg.c_str(), nullptr);
    if(convertedInt < 0) {
      throw std::out_of_range("Negative number is not allowed!");
    }

    return std::optional<unsigned int>(static_cast<unsigned int>(convertedInt));

  } catch(...) {
    return std::nullopt;
  }
}

int
main(int argc, char* argv[])
{
  if(argc != 2) {
    std::cout << "Must insert a number to do calculation.";
    return EXIT_FAILURE;
  }

  auto num = parse_arg(argv[1]);
  if(!num.has_value()) {
    std::cout << "Invalid inserted number.";
    return EXIT_FAILURE;
  }

  std::cout << "You inserted: " << num.value() << std::endl;

  fib_cache fibCache;
  std::cout << calc_fib(num.value(), fibCache) << std::endl;

  return EXIT_SUCCESS;
}