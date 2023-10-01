#include <iostream>
#include <utility>
#include <variant>
#include <vector>

class NotSimple
{
public:
  explicit NotSimple(int, float) {}
};

int
main()
{
  // default initialization: (the first type has to have a default constructor)
  std::variant<int, float> intFloat;
  std::cout << intFloat.index() << ", value " << std::get<int>(intFloat)
            << "\n";

  // monostate for default initialization:
  // std::variant<NotSimple, int> cannot initialize error
  std::variant<std::monostate, NotSimple, int> okInit;
  std::cout << okInit.index() << "\n";

  // pass a value
  std::variant<int, float, std::string> intFloatString{10.5f};
  std::cout << intFloatString.index() << ", value "
            << std::get<float>(intFloatString) << "\n";

  // ambiguity
  // double might convert to float or int, so the compiler cannot decide
  // std::variant<int, float, std::string> wrongVariant{10.5};

  // ambiguity resolved by in_place
  std::variant<long, float, std::string> longFloatString{
    std::in_place_index<1>, 7.6};
  std::cout << longFloatString.index() << ", value "
            << std::get<float>(longFloatString) << "\n";

  // in_place for complex types
  std::variant<std::vector<int>, std::string> vecStr{
    std::in_place_index<0>, {0, 1, 2, 3}};

  // copy-initialize from other variant
  std::variant<int, float> intFloatSecond{intFloat};
  std::cout << intFloatSecond.index() << ", value "
            << std::get<int>(intFloatSecond) << "\n";
}