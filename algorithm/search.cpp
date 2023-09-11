#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int
main()
{
  std::string haystack = "abbabba";
  std::string needle = "bba";

  // std::search and std::find_end algorithms search for a sub-sequence in a
  // sequence. The std::search algorithm will return the first instance, and
  // std::find_end will return the last.
  auto it1 =
    std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
  std::cout << "it1...end = ";
  for(auto it = it1; it != haystack.end(); it++) {
    std::cout << *it;
  }

  std::cout << "\n";

  auto it2 = std::find_end(
    haystack.begin(), haystack.end(), needle.begin(), needle.end()
  );

  std::cout << "it2...end = ";
  for(auto it = it2; it != haystack.end(); it++) {
    std::cout << *it;
  }
}