#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template<typename T>
void
print(T const& input)
{
  std::for_each(input.begin(), input.end(), [](auto const& i) {
    std::cout << i << " ";
  });
}

int
main()
{
  std::vector<int> x{1, 2, 3, 4, 5, 6, 5, 7, 8, 9};
  std::vector<int> res;

  std::remove_copy(x.begin(), x.end(), std::back_inserter(res), 5);
  print(res);

  std::cout << "\n";

  std::string y = "Hello #Cpp Algorithm#";
  std::remove_copy(
    y.begin(), y.end(), std::ostream_iterator<char>(std::cout), '#'
  );
}