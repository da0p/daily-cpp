#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

std::string
timePointAsString(
  std::chrono::time_point<std::chrono::system_clock> const& timePoint
)
{
  std::time_t tp = std::chrono::system_clock::to_time_t(timePoint);
  return std::asctime(std::gmtime(&tp));
}

int
main(int argc, char* argv[])
{
  std::chrono::time_point<std::chrono::system_clock> nowTimePoint =
    std::chrono::system_clock::now();
  std::cout << "Now: " << timePointAsString(nowTimePoint) << "\n";
  auto const thousandYears = std::chrono::hours(24 * 365 * 1000);
  std::chrono::time_point<std::chrono::system_clock> historyTimePoint =
    nowTimePoint - thousandYears;
  std::cout << "Now - 1000 years: " << timePointAsString(historyTimePoint);

  std::chrono::time_point<std::chrono::system_clock> futureTimePoint =
    nowTimePoint + thousandYears;
  std::cout << "Now + 1000 years: " << timePointAsString(futureTimePoint);
}