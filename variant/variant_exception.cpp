#include <iostream>
#include <variant>

class ThrowingClass
{
public:
  explicit ThrowingClass(int i)
  {
    if(i == 0) {
      throw int(10);
    }
  }
  operator int() { throw int(10); }
};

int
main()
{
  std::variant<int, ThrowingClass> v;
  // change the value, exception is thrown in the constructor of the type. This
  // happens before the old value is replaced in the variant, so the variant
  // state is unchanged.
  try {
    v = ThrowingClass(0);
  } catch(...) {
    std::cout << "catch(...)\n";
    // we keep the old state!
    std::cout << v.valueless_by_exception() << "\n";
    std::cout << std::get<int>(v) << "\n";
  }

  // inside emplace, the exception is thrown after the old state of the variant
  // is destroyed. emplace calls operator int to replace the alue, but that
  // throws. After that, the variant is in the wrong state, and we can not
  // recover from the previous state.
  try {
    // calls the operator int
    v.emplace<0>(ThrowingClass(10));
  } catch(...) {
    std::cout << "catch(...)\n";
    // the old state was destroyed, so we're not in invalid state!
    // valueless_by_exception is an invalid state. Accessing a value from such
    // variant is not possible.
    // In this case, variant::index returns variant_npos, and std::get and
    // std::visit will throw bad_variant_access.
    std::cout << v.valueless_by_exception() << "\n";
  }

  return 0;
}