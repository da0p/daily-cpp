#include <iostream>
#include <vector>

class Product
{
public:
  explicit Product(int id, std::string const& name)
    : id_{id}
    , name_{name}
  {
    std::cout << "Product(): " << id_ << ", " << name_ << "\n";
  }

  Product(Product const& other)
    : id_{other.id_}
    , name_{other.name_}
  {
    std::cout << "Product(copy): " << id_ << ", " << name_ << "\n";
  }

  // Mark move constructor as noexcept will allow optimisations.
  Product(Product&& other) noexcept
    : id_{other.id_}
    , name_{std::move(other.name_)}
  {
    std::cout << "Product(move): " << id_ << ", " << name_ << "\n";
  }

  /*
  Product(Product&& other)
    : id_{other.id_}
    , name_{std::move(other.name_)}
  {
    std::cout << "Product(move): " << id_ << ", " << name_ << "\n";
  }
  */

  std::string const& name() const { return name_; }

private:
  int id_;
  std::string name_;
};

int
main()
{
  Product tvSet{100, "tv set"};
  std::cout << tvSet.name() << " created...\n";
  Product setV2{std::move(tvSet)};
  std::cout << setV2.name() << " created...\n";
  std::cout << "old value: " << tvSet.name() << "\n";

  // When the move constructor is not marked with noexcept then the container
  // has to be prepared for a case where it tries to copy elements to a new
  // buffer, and at some point, one operation throws. The only way to revert to
  // a safe situation is to abandon the copy. When move noexcept is available,
  // then the vector implementation can assume that there's no exception
  // happending, and moving will be "safe" for all elements.
  std::vector<Product> prods;
  prods.emplace_back(101, "car");
  prods.emplace_back(202, "box");
  prods.emplace_back(303, "toy");
  prods.emplace_back(404, "mug");
  prods.emplace_back(505, "pencil");
}