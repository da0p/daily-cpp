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
    {"Peter", 100}, {"John", 50}, {"Harley", 75}, {"James", 69}, {"Leon", 87}};

  auto pp = std::partition(
    examResult.begin(),
    examResult.end(),
    [threshold = 69](auto const& r) { return r.score >= threshold; }
  );

  auto print = [](auto const& v, auto const& pp) {
    // let's print who passes
    for(auto it = v.begin(); it != pp; it++) {
      std::cout << "[PASS] " << it->name << ", " << it->score << "\n";
    }

    for(auto it = pp; it != v.end(); it++) {
      std::cout << "[FAIL] " << it->name << ", " << it->score << "\n";
    }
  };

  print(examResult, pp);

  std::cout << "\n\n";

  std::vector<ExamResult> physics{
    {"Peter", 100}, {"John", 50}, {"Harley", 75}, {"James", 69}, {"Leon", 87}};

  // std::stable_partition will keep the relative order of elements in both
  // partition while std::partition does not
  auto omega = std::stable_partition(
    physics.begin(),
    physics.end(),
    [threshold = 69](auto const& r) { return r.score >= threshold; }
  );

  print(physics, omega);
}