#include <algorithm>
#include <atomic>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

struct ExpensieToCopy
{
  int counter{};
};

int
getRandom(int begin, int end)
{
  std::random_device seed;     // initial randomness
  std::mt19937 engine(seed()); // generator
  std::uniform_int_distribution<> uniformDist(begin, end);

  return uniformDist(engine);
}

void
count(ExpensieToCopy& exp)
{
  std::vector<std::thread> v;
  std::atomic_ref<int> counter{exp.counter};

  for(int n = 0; n < 10; ++n) {
    v.emplace_back([&counter] {
      auto randomNumber = getRandom(100, 200);
      for(int i = 0; i < randomNumber; ++i) {
        ++counter;
      }
    });
  }

  for(auto& t : v) {
    t.join();
  }
}

int
main()
{

  std::cout << "\n";

  ExpensieToCopy exp;
  count(exp);
  std::cout << "exp.counter: " << exp.counter << "\n\n";

  return EXIT_SUCCESS;
}