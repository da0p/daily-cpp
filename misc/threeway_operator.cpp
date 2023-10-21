#include <cassert>
#include <compare>
#include <cstdint>
#include <iostream>

/**
 * @note
 * - Default three-way operator performs member-wise comparison
 * - Can provide a manual version of three-way operator
 *
 * Different comparison categories:
 * Three categories of comparisons
 * - equality: only operator= and operator!=;
 * - ordering: all comparison operators;
 * - neither: none of the comparison operators.
 *
 * Comparison strength or category strength:
 * - Equal and equivalent are different. Equal meaning is stronger than
 * equivalent. Equal is used in strong ordering, equivalent is used in weak
 * ordering.
 *
 * - Use strong ordering if everything that is copied, in copy constructor, is
 * also a part of the comparison.
 * - Use weak ordering if only a subset of what is copied is compared. Subset
 * also means that, if the comparison is done in a special way, as in
 * case-insensitive comparison of a string, the strength is also weak.
 *
 * - strong_ordering and weak_odering have three different possible values:
 * greater, equivalent, and less.
 *
 * - partial_odering has the same three values as weak_odering: greater,
 * equivalent, and less. But it has an additional value: unordered. We should
 * use this whenever we have a type that is not fully orderable. Example: Not a
 * Number (NaN)
 *
 * - strong_odering can be converted into a weak_ordering (we lose some
 * requirements). The other way around isn't possible, of course, there is no
 * way to add requirements to a type.
 *
 *
 * One cool thing about C++20 compiler is that it can reverse and rewrite
 * comparisons.
 */

struct Weak
{
  int32_t value;
  std::weak_ordering operator<=>(Weak const&) const = default;
};

struct Strong
{
  int32_t value;
  std::strong_ordering operator<=>(Strong const&) const = default;
};

struct Combined
{
  Weak w;
  Strong s;

  // compiler deduced the return ordering automatically
  auto operator<=>(Combined const&) const = default;
};

/**
 * Custom sort
 */
struct Address
{
  std::string city;
  std::string street;
  uint32_t street_no;

  auto operator<=>(Address const& rhs) const
  {
    // Sort city and street using their <=>
    if(auto const& cmp = city <=> rhs.city; cmp != 0) {
      return cmp;
    } else if(auto const& cmp = street <=> rhs.street; cmp != 0) {
      return cmp;
    }

    // sort street_no ascending
    return rhs.street_no <=> street_no;
  }

  // default should be good enough for equal operator
  bool operator==(Address const&) const = default;
};

int
main()
{
  Combined combined_1{.w{.value = 10}, .s{.value = 20}};
  Combined combined_2{.w{.value = 10}, .s{.value = 20}};
  assert(combined_1 == combined_2);

  Combined combined_3{.w{.value = 20}, .s{.value = 10}};
  assert(combined_1 < combined_3);

  Address address_1{.city = "Milan", .street = "ddd", .street_no = 10};
  Address address_2{.city = "Milan", .street = "ddd", .street_no = 10};
  Address address_3{.city = "Milan", .street = "ddd", .street_no = 20};

  assert(address_1 == address_2);
  assert(address_1 > address_3);
}