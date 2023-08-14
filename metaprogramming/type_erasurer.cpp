#include <iostream>
#include <memory>
#include <vector>

/**
 * Type Erasurer
 *
 * Type erasurer is a pattern in which type information is removed, allowing
 * types that are not necessarily related to be treated in a generic way.
 *
 * We use type erasurer when we treat unrelated types in a similar matter (a
 * process called duck typing) but we are not able to change those types.
 *
 * - One way to achieve it is through void pointer, but it's not C++
 *
 */
struct knight
{
  void attack() { std::cout << "draw sword\n"; }
};

struct mage
{
  void attack() { std::cout << "spell magic curse\n"; }
};

struct game
{
  struct game_unit
  {
    virtual void attack() = 0;
    virtual ~game_unit() = default;
  };

  template<typename T>
  struct game_unit_wrapper : public game_unit
  {
    game_unit_wrapper(T& unit)
      : t(unit)
    {
    }
    void attack() override { t.attack(); }

  private:
    T& t;
  };

  template<typename T>
  void addUnit(T& unit)
  {
    units.push_back(std::make_unique<game_unit_wrapper<T>>(unit));
  }

  void fight()
  {
    for(auto& u : units) {
      u->attack();
    }
  }

private:
  std::vector<std::unique_ptr<game_unit>> units;
};

// Formal way
struct unit
{
  template<typename T>
  unit(T&& obj)
    : unit_(std::make_shared<unit_model<T>>(std::forward<T>(obj)))
  {
  }

  void attack() { unit_->attack(); }

  // Concept provides the common required interface that an object is required
  // to have in order to be treated correctly
  struct unit_concept
  {
    virtual void attack() = 0;
    virtual ~unit_concept() = default;
  };

  // This acts like a wrapper, erasing the previous type, and consider it as
  //  a model type
  template<typename T>
  struct unit_model : public unit_concept
  {
    unit_model(T& unit)
      : t(unit)
    {
    }

    void attack() override { t.attack(); }

  private:
    T& t;
  };

private:
  std::shared_ptr<unit_concept> unit_;
};

void
fight(std::vector<unit>& units)
{
  for(auto& u : units) {
    u.attack();
  }
}

int
main()
{
  knight k;
  mage m;

  game g;
  game::game_unit_wrapper ku{k};
  game::game_unit_wrapper mu{m};

  g.addUnit(ku);
  g.addUnit(mu);
  g.fight();

  // formal
  std::vector<unit> v{unit{k}, unit{m}};
  fight(v);
}