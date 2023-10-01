#include <iostream>
#include <optional>
#include <string>
#include <utility>

void*
operator new(std::size_t count)
{
  std::cout << "allocating " << count << " bytes"
            << "\n";
  return malloc(count);
}

void
operator delete(void* ptr) noexcept
{
  std::cout << "global op delete called\n";
  std::free(ptr);
}

class UserName
{
public:
  ~UserName() { std::cout << "UserName::~UserName('" << mName << "')\n"; }

  explicit UserName()
    : mName("Default")
  {
    std::cout << "UserName::UserName('" << mName << "')\n";
  }

  explicit UserName(std::string const& str)
    : mName(str)
  {
    std::cout << "UserName::UserName('" << mName << "')\n";
  }

  explicit UserName(UserName const& u)
    : mName(u.mName)
  {
    std::cout << "UserName::UserName(copy '" << mName << "')\n";
  }

  UserName& operator=(UserName const& u)
  {
    // copy assignment
    mName = u.mName;

    std::cout << "UserName::=(copy '" << mName << "')\n";

    return *this;
  }

  UserName& operator=(UserName&& u) noexcept
  {
    // move assignment
    mName = std::move(u.mName);
    std::cout << "UserName::=(move '" << mName << "')\n";

    return *this;
  }

private:
  std::string mName;
};

int
main()
{
  // Copy constructor will be called
  std::optional<UserName> opt(UserName{});

  // Create the optional in place, no copy constructor is called
  auto anotherOpt = std::make_optional<UserName>();

  // another way to create optionl in place
  auto anotherAnotherOpt = std::optional<UserName>(std::in_place);

  // No temporary object created
  auto holaOpt = std::optional<UserName>("Hello");
}