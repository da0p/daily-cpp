#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int
main(int argc, char* argv[])
{
  std::vector<int> scores = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::cout << std::accumulate(
                 scores.cbegin(), scores.cend(), 1, std::multiplies<int>()
               )
            << std::endl;

  // Use accumulate to filter elements

  auto const lowerLimit = 4;
  auto bigScoreFilter = [lowerLimit](std::vector<int> previous, int score) {
    if(score > lowerLimit) {
      previous.push_back(score);
    }

    return previous;
  };

  auto const bigScores = std::accumulate(
    scores.cbegin(), scores.cend(), std::vector<int>{}, bigScoreFilter
  );

  std::for_each(bigScores.cbegin(), bigScores.cend(), [](int score) {
    std::cout << score << ", ";
  });

  return 0;
}
