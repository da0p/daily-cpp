#include <atomic>
#include <iostream>
#include <set>
#include <vector>

/**
 * Curiously Recurring Template Pattern
 *
 * - There is a base class template that defines that (static) interface.
 * - Derived classes are themselves the template argument for the base class
 *   template.
 * - The member functions of the base class call member functions of its type
 *   template parameter (which are the derived classes).
 *
 * When to use CRTP
 *
 * - Limiting the number of times a type can be instantiated
 * - Adding common functionality and avoiding code duplication
 * - Implementing the composite design pattern
 *
 */

template<typename T>
struct game_unit
{
  void attack() { static_cast<T*>(this)->do_attack(); }
};

struct knight : game_unit<knight>
{
  void do_attack() { std::cout << "draw sword\n"; }
};

struct mage : game_unit<mage>
{
  void do_attack() { std::cout << "draw wand\n"; }
};

template<typename T>
void
fight(std::vector<game_unit<T>*> const& units)
{
  for(auto const& unit : units) {
    unit->attack();
  }
}

/**
 * 1st Use case: Limiting the object count with CRTP
 *
 */
template<typename T, size_t N>
struct limited_instances
{
  static std::atomic<size_t> count;
  limited_instances()
  {
    if(count >= N) {
      throw std::logic_error{"Too many instances"};
    }
    ++count;
  }
  ~limited_instances() { --count; }
};

template<typename T, size_t N>
std::atomic<size_t> limited_instances<T, N>::count = 0;

struct excalibur : limited_instances<excalibur, 1>
{};

struct book_of_magic : limited_instances<book_of_magic, 3>
{};

/**
 * 2nd Use case: Adding functionality with CRTP
 *
 *
 */
template<typename T>
struct movable_unit
{
  void advance(size_t steps)
  {
    while(steps--) {
      static_cast<T*>(this)->step_forth();
    }
  }

  void retreat(size_t steps)
  {
    while(steps--) {
      static_cast<T*>(this)->step_back();
    }
  }
};

struct knight_2 : movable_unit<knight_2>
{
  void step_forth() { std::cout << "knight moves forward\n"; }
  void step_back() { std::cout << "knight moves back\n"; }
};

struct mage_2 : movable_unit<mage_2>
{
  void step_forth() { std::cout << "mage moves forward\n"; }
  void step_back() { std::cout << "mage moves back\n"; }
};

/**
 * 3rd Use case: Implementing composite design pattern
 *
 * Composite design pattern is meant to treat objects uniformly
 *
 */

template<typename T>
struct base_unit
{
  template<typename U>
  void ally_with(U& other);
};

struct hero : base_unit<hero>
{
  hero(std::string_view n)
    : name(n)
  {
  }
  hero* begin() { return this; }
  hero* end() { return this + 1; }

private:
  std::string name;
  std::set<hero*> connections;

  template<typename U>
  friend struct base_unit;

  template<typename U>
  friend std::ostream& operator<<(std::ostream& os, base_unit<U>& object);
};

struct hero_party
  : std::vector<hero>
  , base_unit<hero_party>
{};

template<typename T>
template<typename U>
void
base_unit<T>::ally_with(U& other)
{
  for(hero& from : *static_cast<T*>(this)) {
    for(hero& to : other) {
      from.connections.insert(&to);
      to.connections.insert(&from);
    }
  }
}

template<typename T>
std::ostream&
operator<<(std::ostream& os, base_unit<T>& object)
{
  for(hero& obj : *static_cast<T*>(&object)) {
    for(hero* n : obj.connections) {
      os << obj.name << " --> [" << n->name << "]"
         << "\n";
    }
  }

  return os;
}

int
main()
{
  knight k;
  mage m;

  fight<knight>({&k});
  fight<mage>({&m});

  // 1st use case
  excalibur e1;
  try {
    excalibur e2;
  } catch(std::exception& e) {
    std::cout << e.what() << "\n";
  }
  book_of_magic b1;
  book_of_magic b2;
  book_of_magic b3;
  try {
    book_of_magic b4;
  } catch(std::exception& e) {
    std::cout << e.what() << "\n";
  }

  // 2nd use case
  knight_2 k2;
  mage_2 m2;
  k2.advance(3);
  k2.retreat(2);

  m2.advance(3);
  m2.retreat(3);

  // 3rd use case
  hero h1("Arthur");
  hero h2("Lancelot");
  hero_party p1;
  p1.emplace_back("Bors");
  hero_party p2;
  p2.emplace_back("Cador");
  p2.emplace_back("Constantine");

  h1.ally_with(h2);
  h1.ally_with(p1);

  p1.ally_with(h2);
  p1.ally_with(p2);

  std::cout << h1 << "\n";
  std::cout << h2 << "\n";
  std::cout << p1 << "\n";
  std::cout << p2 << "\n";
}