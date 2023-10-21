#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct ExamResult
{
  std::string name;
  uint32_t score;
};

int
main()
{
  std::vector<ExamResult> examResult{
    {"John", 25},
    {"James", 45},
    {"Doe", 50},
    {"Carter", 59},
    {"Rihana", 65},
    {"Peter", 78},
    {"Ez", 87},
    {"Eric", 100}};

  // std::lower_bound returns the first element for which elem < value
  // std::upper_bound returns the first element for which value < elem
  // if no such element exists, both algorithms return the end iterator
  auto lb = std::ranges::lower_bound(examResult, 49, {}, &ExamResult::score);
  auto ub = std::ranges::upper_bound(examResult, 99, {}, &ExamResult::score);

  for(auto it = examResult.begin(); it != lb; it++) {
    std::cout << "[LOWER] " << it->name << ", " << it->score << "\n";
  }

  for(auto it = lb; it != ub; it++) {
    std::cout << "[MIDDLE] " << it->name << ", " << it->score << "\n";
  }

  for(auto it = ub; it != examResult.end(); it++) {
    std::cout << "[UPPER] " << it->name << ", " << it->score << "\n";
  }
}