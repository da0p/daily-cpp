#include <exception>
#include <iostream>
#include <stdexcept>

class Product
{
public:
  Product(int id, unsigned quantity, std::string const& name)
    : id_{id}
    , quantity_{quantity}
    , name_{name}
  {
    verifyData();
  }

  Product(std::string const& name)
    : Product{0, 0, name}
  {
  }

  void verifyData()
  {
    if(quantity_ > MaxQuantity) {
      throw std::invalid_argument("quantity is too large!");
    }
  }

  std::string const& getName() const { return name_; }

private:
  int id_;
  unsigned quantity_;
  std::string name_;
  static constexpr unsigned MaxQuantity = 100;
};

int
main()
{
  try {
    Product box{"a box"};
    std::cout << "product: " << box.getName() << " created...\n";

    Product toy{101, 200, "a box"};
    std::cout << "product: " << toy.getName() << " created...\n";
  } catch(std::exception const& e) {
    std::cout << "cannot create: " << e.what() << "\n";
  }
}