#include <iostream>
#include <map>
#include <vector>

struct Product
{
  Product() = default;
  Product(std::string s, double v)
    : name{std::move(s)}
    , value{v}
  {
  }

  std::string name;
  double value{};
};

class Package
{
public:
  void addProduct(Product const& p)
  {
    ++counts_[p.name];
    prods_.push_back(p);
    totalValue_ += p.value;
  }

  void printContents() const
  {
    for(auto& [key, val] : counts_) {
      std::cout << key << ", count: " << val << "\n";
    }
    std::cout << "total value: " << totalValue_ << "\n";
  }

private:
  std::vector<Product> prods_;
  std::map<std::string, unsigned> counts_;
  double totalValue_{};
};

int
main()
{
  Package pack;
  pack.addProduct({"crayons", 3.0});
  pack.addProduct({"pen", 2.0});
  pack.addProduct({"bricks", 11.0});
  pack.addProduct({"bricks", 12.0});
  pack.addProduct({"pen", 12.0});
  pack.addProduct({"pencil", 12.0});
  pack.printContents();
}