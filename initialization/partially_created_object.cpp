#include <iostream>

class Product
{
public:
  explicit Product(char const* name, unsigned id)
    : name_{name}
    , id_{id}
  {
    std::cout << name << ", id " << id << "\n";
    if(id < 100) {
      throw std::runtime_error{"bad id..."};
    }
  }

private:
  std::string name_;
  unsigned id_;
};

int
main()
{
  // The compilers calls a destruct only for objects that are fully created.
  try {
    Product tvset{"TV Set", 123};
    Product car{"Mistang", 9};
  } catch(std::exception const& e) {
    std::cout << "exception: " << e.what() << "\n";
  }
}