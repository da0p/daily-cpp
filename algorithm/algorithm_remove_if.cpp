#include <algorithm>
#include <iostream>
#include <vector>

enum class Gender : uint8_t
{
  MALE,
  FEMALE,
};

struct person_t
{
  std::string name;
  uint8_t age;
  Gender gender;
};

int
main(int argc, char* argv[])
{
  std::vector<person_t> people = {
    {"Alex", 25, Gender::FEMALE},
    {"Max", 65, Gender::MALE},
    {"Rin", 10, Gender::FEMALE},
    {"Nya", 34, Gender::FEMALE},
    {"Lyx", 45, Gender::MALE},
  };

  std::cout << "Size before using remove_if: " << people.size() << "\n";
  // remove_if does not actually remove the item, but return the iterator to the
  // first item satisying the predicate
  auto it = std::remove_if(people.begin(), people.end(), [](auto&& person) {
    return person.gender == Gender::FEMALE;
  });

  std::cout << "Size after using remove_if: " << people.size() << "\n";

  auto print = [](auto&& people) {
    std::for_each(people.begin(), people.end(), [](auto&& person) {
      std::cout << "--------------------------------\n";
      std::cout << "Name: " << person.name << "\n";
      std::cout << "Age: " << static_cast<uint32_t>(person.age) << "\n";
      std::cout << "Gender: " << static_cast<uint32_t>(person.gender) << "\n";
    });
  };

  // remove_if moves the deleted item at the end, using erase to
  // remove the item and shrink the size
  people.erase(it, people.end());

  std::cout << "Size after using erase: " << people.size() << "\n";

  print(people);

  return 0;
}
