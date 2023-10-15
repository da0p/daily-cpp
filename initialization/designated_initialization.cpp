#include <iostream>
#include <string>
#include <vector>

/**
 * Note: Designated initialization
 * Rules:
 * - Designated initializers work only for aggregate initialization, so they
 *   only support aggregate types,
 * - Designated initialization requires braces {} and doesn't support C++20
 *   initialization with parens (),
 * - Designators can only refer to non-static data members,
 * - Designators in the initialization expression must have the same order of
 *   data members in a class declaration, unlike C language, where you can put
 *   designators in any order.
 * - Not all data members must be specified in the expression,
 * - You cannot mix regular initialization with designators,
 * - There can only be one designator for a data member,
 * - You cannot nest designators.
 */

struct Product
{
  std::string name_;
  bool inStock_{false};
  double price_ = 0.0;
};

void
print(Product const& p)
{
  std::cout << "name: " << p.name_ << ", in stock: " << std::boolalpha
            << p.inStock_ << ", price: " << p.price_ << "\n";
}

struct Time
{
  int hour;
  int minute;
};

struct Date
{
  Time t;
  int year;
  int month;
  int day;
};

struct Team
{
  std::string name;
  std::string where;
};

struct GameSession
{
  std::string game;
  std::string localication;
  std::vector<Team> teams;
  Date date;
};

int
main()
{
  Product p{.name_ = "box", .inStock_ = true};
  print(p);

  Date d{.t{.hour = 10, .minute = 35}, .year = 2050, .month = 5, .day = 10};

  // The following syntax doesn't work, can't nest designators
  // Date d{.t.hour=10, .t.minute = 35, .year = 2050, .month = 5, .day = 10};

  // pass to a function
  print({.name_ = "tv", .inStock_ = true, .price_ = 100.0});

  // not all members used
  print({.name_ = "car", .price_ = 2000.0});

  // Can use designated initialization inside another designated initialization
  GameSession test{
    .game = "Pong",
    .localication = "Pacific Ocean",
    .teams =
      {
        Team{
          .name = "Johny Test",
          .where = "Arctica",
        },
        Team{
          .name = "Jane Doe",
          .where = "Antarctic",
        },
      },
    .date =
      {
        .year = 2022,
        .month = 10,
        .day = 6,
      },
  };
}