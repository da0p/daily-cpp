#include <array>
#include <format>
#include <iostream>
#include <vector>

int
main()
{

  std::vector<char> buffer{};
  // std::format_to can be used to format a string directly into a dynamic
  // buffer. This is the bad way of doing so since the existing data has to
  // be copied over, and the former memory is freed.
  std::format_to(std::back_inserter(buffer), "{}, {}", "Hello", "World");

  for(auto const& c : buffer) {
    std::cout << c;
  }

  std::cout << "\n\n";

  // we can use std::formated_size to get the size and pre-allocate the buffer
  constexpr auto fmt{"{}, {}"};

  auto const size = std::formatted_size(fmt, "Hello", "World");

  // preallocate the required memory
  std::vector<char> buffer_2(size);
  std::format_to(buffer_2.begin(), fmt, "Hello", "World");
  for(auto const& c : buffer_2) {
    std::cout << c;
  }

  std::cout << "\n\n";

  std::array<char, 10> buffer_3{};
  std::format_to_n(
    buffer_3.data(), buffer_3.size() - 1, "{}, {}", "Hello", "World"
  );
  for(auto const& c : buffer_3) {
    std::cout << c;
  }

  return 0;
}