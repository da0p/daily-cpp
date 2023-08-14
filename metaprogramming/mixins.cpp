#include <iostream>
#include <memory>
#include <vector>

/**
 * Mixins
 *
 * - Mixins are small classes that are designed to add functionality to other
 *   classes.
 * - The point of mixins is that they are supposed to add functionality to
 *   classes without being a base class to them, which is the key to the CRTP
 *   pattern. Instead, mixins are supposed to inherit from the classes they
 *   add functionality to, which is the CRTP upside down.
 *
 */

struct knight
{
  void step_forth() { std::cout << "knight moves forward\n"; }

  void step_back() { std::cout << "knight moves back\n"; }
};

struct mage
{
  void step_forth() { std::cout << "mage moves forward\n"; }

  void step_back() { std::cout << "mage moves back\n"; }
};

template<typename T>
struct movable_unit : public T
{
  void advance(size_t steps)
  {
    while(steps--) {
      T::step_forth();
    }
  }

  void retreat(size_t steps)
  {
    while(steps--) {
      T::step_back();
    }
  }
};

struct aggressive_style
{
  void fight() { std::cout << "attack! attack attack!\n"; }
};

struct moderate_style
{
  void fight() { std::cout << "attack then defend\n"; }
};

template<typename T>
struct lone_warrior : public T
{
  void fight()
  {
    std::cout << "fighting alone.";
    T::fight();
  }
};

template<typename T>
struct team_warrior : public T
{
  void fight()
  {
    std::cout << "fighting with a team.";
    T::fight();
  }
};

struct game_unit
{
  virtual void attack() = 0;
  virtual ~game_unit() = default;
};

template<typename T>
struct knight_2
  : T
  , game_unit
{
  void attack()
  {
    std::cout << "draw sword.";
    T::fight();
  }
};

template<typename T>
struct mage_2
  : T
  , game_unit
{
  void attack()
  {
    std::cout << "spell magic curse.";
    T::fight();
  }
};

int
main()
{
  movable_unit<knight> k;
  k.advance(3);
  k.retreat(2);

  movable_unit<mage> m;
  m.advance(3);
  m.retreat(1);

  std::vector<std::unique_ptr<game_unit>> units;
  units.emplace_back(std::make_unique<knight_2<aggressive_style>>());
  units.emplace_back(std::make_unique<knight_2<moderate_style>>());
  units.emplace_back(std::make_unique<mage_2<aggressive_style>>());
  units.emplace_back(std::make_unique<mage_2<moderate_style>>());
  units.emplace_back(std::make_unique<knight_2<lone_warrior<aggressive_style>>>(
  ));
  units.emplace_back(std::make_unique<knight_2<team_warrior<aggressive_style>>>(
  ));
  units.emplace_back(std::make_unique<knight_2<lone_warrior<moderate_style>>>()
  );
  units.emplace_back(std::make_unique<knight_2<team_warrior<moderate_style>>>()
  );
  units.emplace_back(std::make_unique<mage_2<lone_warrior<aggressive_style>>>()
  );
  units.emplace_back(std::make_unique<mage_2<team_warrior<aggressive_style>>>()
  );
  units.emplace_back(std::make_unique<mage_2<lone_warrior<moderate_style>>>());
  units.emplace_back(std::make_unique<mage_2<team_warrior<moderate_style>>>());

  for(auto& u : units) {
    u->attack();
  }
}