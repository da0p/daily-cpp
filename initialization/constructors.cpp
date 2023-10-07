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

  Product& operator=(Product const& other)
  {
    if(this == &other) {
      return *this;
    }
    id_ = other.id_;
    name_ = other.name_;
    std::cout << "operator=(copy): " << id_ << ", " << name_ << "\n";
    return *this;
  }

  // move assignment operator
  Product& operator=(Product&& other) noexcept
  {
    id_ = other.id_;
    name_ = std::move(other.name_);
    std::cout << "operator=(move): " << id_ << ", " << name_ << "\n";
    return *this;
  }

  std::string const& name() const { return name_; }

private:
  int id_;
  std::string name_;
};

int
main()
{
  std::cout << "Move ctor marked with noexcept:\n\n";
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
  std::cout << "\n\n";

  std::cout << "Copy assignment operators:\n\n";
  // copy and move assignment operators
  // The compiler calls a copy constructor when you initialize an object. When
  // an entity already exists, the program runs an assignment operation.
  Product base{42, "base"};
  Product first{base};    // copy ctor called!
  Product second = first; // copy ctor called!
  Product third{100, "third"};
  third = second; // assignment operator called!
  std::cout << "\n\n";

  std::cout << "Move assignment operators:\n\n";
  // Move assignment operators
  Product base2{42, "base"};
  Product first2{std::move(base)}; // move ctor called!
  std::cout << "base2.name() after mvoe: " << base2.name() << "\n";
  Product second2 = std::move(first); // move ctor called!
  std::cout << "first2.name() after move: " << first2.name() << "\n";
  Product third2{100, "third"};
  third2 = std::move(second2); // assignment operator called!
  std::cout << "second2.name() after move: " << second2.name() << "\n";
}