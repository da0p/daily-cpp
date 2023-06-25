#include <array>
#include <bits/ranges_algo.h>
#include <iostream>
#include <list>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>

template<typename T>
void
printMovies(T movies)
{
  std::for_each(movies.begin(), movies.end(), [](auto const& movie) {
    std::cout << "{" << movie.name << ", " << movie.rating << "}\n";
  });
}

struct Movie
{
  std::string name;
  float rating;
};

int
main(int argc, char* argv[])
{
  std::list<Movie> movies{
    {"GameOfThrones", 4.5},
    {"EndGame", 5.0},
    {"X-Men", 3.0},
    {"BigBangTheory", 5.0},
    {"AliceInBorderLand", 3.9}};

  // create a view of good movies with rating > 4.0
  auto goodMovies = movies | std::views::filter([](auto const& movie) {
                      return movie.rating > 4.0;
                    });
  printMovies(goodMovies);

  std::cout << "\n------------------------------\n";
  for(auto const& movie : goodMovies | std::views::take(2)) {
    std::cout << "{" << movie.name << ", " << movie.rating << "}\n";
  }

  return EXIT_SUCCESS;
}