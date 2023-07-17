#include <cstdlib>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

static int const NUM = 10000000;

long long
getDorProduct(std::vector<int>& v, std::vector<int>& w)
{
  auto vSize = v.size();

  auto fut1 = std::async([&] {
    return std::inner_product(&v[0], &v[vSize / 4], &w[0], 0LL);
  });

  auto fut2 = std::async([&] {
    return std::inner_product(&v[vSize / 4], &v[vSize / 2], &w[vSize / 4], 0LL);
  });

  auto fut3 = std::async([&] {
    return std::inner_product(
      &v[vSize * 3 / 4], &v[vSize], &w[vSize * 3 / 4], 0LL
    );
  });

  auto fut4 = std::async([&] {
    return std::inner_product(
      &v[vSize * 3 / 4], &v[vSize], &w[vSize * 3 / 4], 0LL
    );
  });

  return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int
main(int argc, char* argv[])
{
  std::random_device seed;

  // generator
  std::mt19937 engine(seed());

  // distribution
  std::uniform_int_distribution<int> dist(0, 100);

  // fill the vectors
  std::vector<int> v, w;
  v.reserve(NUM);
  w.reserve(NUM);
  for(int i = 0; i < NUM; i++) {
    v.push_back(dist(engine));
    w.push_back(dist(engine));
  }

  std::cout << "getDotProduct(v, w): " << getDorProduct(v, w) << "\n";

  return EXIT_SUCCESS;
}