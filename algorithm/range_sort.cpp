#include <algorithm>
#include <bits/ranges_cmp.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <vector>

struct Person
{
  std::string name;
  uint32_t age;
};

void
print(auto const& seq)
{
  for(auto const& elem : seq) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

void
print(std::vector<Person> const& people)
{
  std::for_each(people.begin(), people.end(), [](auto const& person) {
    std::cout << "[" << person.name << ", " << person.age << "]\n";
  });
  std::cout << "\n---------------------------------------\n";
}

int
main(int argc, char* argv[])
{

  std::vector<int> x{2, -1, 300, 200, 20, 10};
  std::ranges::sort(x);
  print(x);

  std::ranges::sort(x, std::ranges::greater());
  print(x);

  std::vector<Person> people{
    {"John", 13}, {"Nick", 26}, {"Peter", 45}, {"Lynn", 33}};

  std::ranges::sort(people, {}, &Person::age);
  print(people);

  std::ranges::sort(people, std::ranges::greater(), &Person::age);
  print(people);

  std::ranges::sort(people, [](auto const& person_1, auto const& person_2) {
    return person_1.name > person_2.name;
  });
  print(people);

  return EXIT_SUCCESS;
}