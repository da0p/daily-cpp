#include <algorithm>
#include <charconv>
#include <iostream>
#include <ranges>
#include <vector>

int
main()
{
  std::string version = "1.23.13.42";
  std::vector<int> parsed;

  // std::views::split split a range into a view over sub-ranges.
  // std::views::split maintains he bidirectional, random access or contiguous
  // properties of the underlying range
  std::ranges::copy(
    version | std::views::split('.') | std::views::transform([](auto v) {
      int result = 0;
      std::from_chars(v.data(), v.data() + v.size(), result);
      return result;
    }),
    std::back_inserter(parsed)
  );

  std::string_view data = "Car Dog Window";
  std::vector<std::string> words;
  std::ranges::for_each(
    data | std::views::lazy_split(' '),
    [&words](auto const& view) {
      // string constructor needs common range.
      auto common = view | std::views::common;
      words.emplace_back(common.begin(), common.end());
    }
  );
  // words == {"Car", "Dog", "Window"}

  auto joined =
    data | std::views::lazy_split(' ') | std::views::join | std::views::common;

  std::string out(joined.begin(), joined.end());

  std::cout << "out = " << out << "\n";
}