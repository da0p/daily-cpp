#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int
main(int argc, char* arv[])
{
  // std::istream_iterator reads successive objects of type T from
  // std::basic_istream object for which it was constructed.
  // Default constructor of std::istream_iterator is known as the end-of-stream
  // iterator.

  std::istringstream input{"1 2 3 4 5 6"};
  std::copy(
    std::istream_iterator<int>(input),
    std::istream_iterator<int>(),
    std::ostream_iterator<int>(std::cout, " x ")
  );

  std::cout << "\n--------------------------------------\n";
  // std::ostream_iterator writes successive objects of type T into the
  // std::basic_ostream object for which it was constructed.
  // With std::ostream, an optinal delim can be put there.
  std::vector<int> numbers = {1, 99, 100, 23, 45};
  std::copy(
    numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " - ")
  );

  return 0;
}
