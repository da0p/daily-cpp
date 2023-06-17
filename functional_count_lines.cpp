#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

std::ifstream
open_file(std::string const& filename)
{
  std::ifstream in(filename);

  return in;
}

uint32_t
count_lines(std::ifstream in)
{
  return std::count(
    std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), '\n'
  );
}

std::vector<uint32_t>
count_lines_in_files(std::vector<std::string> const& files)
{
  std::vector<uint32_t> result;
  std::ranges::for_each(
    files | std::views::transform(open_file) |
      std::views::transform(count_lines),
    [&result](uint32_t counter) { result.push_back(counter); }
  );

  return result;
}

int
main(int argc, char* argv[])
{
  auto const ints = {0, 1, 2, 3, 4, 5};
  auto even = [](int i) { return 0 == i % 2; };
  auto square = [](int i) { return i * i; };

  std::ranges::for_each(
    ints | std::views::filter(even) | std::views::transform(square),
    [](int i) { std::cout << i << " "; }
  );

  std::cout << "\n-----------------Breaking line -----------------\n";
  std::vector<std::string> files{};
  for(uint32_t i = 1; i < argc; i++) {
    files.push_back(argv[i]);
  }

  auto result = count_lines_in_files(files);
  std::ranges::for_each(result, [](uint32_t counter) {
    std::cout << counter << " ";
  });

  return 0;
}
