#include <algorithm>
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
    {"Peter", 100}, {"John", 50}, {"Harley", 75}, {"James", 69}, {"Leon", 87}};

  auto pp = std::partition(
    examResult.begin(),
    examResult.end(),
    [threshold = 69](auto const& r) { return r.score >= threshold; }
  );

  // let's print who passes
  for(auto it = examResult.begin(); it != pp; it++) {
    std::cout << "[PASS] " << it->name << ", " << it->score << "\n";
  }

  for(auto it = pp; it != examResult.end(); it++) {
    std::cout << "[FAIL] " << it->name << ", " << it->score << "\n";
  }
}