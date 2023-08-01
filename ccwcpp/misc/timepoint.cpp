#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

int
main(int argc, char* argv[])
{
  std::chrono::time_point<std::chrono::system_clock> sysTimePoint;
  std::time_t tp = std::chrono::system_clock::to_time_t(sysTimePoint);
  std::string sTp = std::asctime(std::gmtime(&tp));
  std::cout << "Epoch: " << sTp << "\n";

  tp = std::chrono::system_clock::to_time_t(sysTimePoint.min());
  sTp = std::asctime(std::gmtime(&tp));
  std::cout << "Time min: " << sTp << "\n";

  tp = std::chrono::system_clock::to_time_t(sysTimePoint.max());
  sTp = std::asctime(std::gmtime(&tp));
  std::cout << "Time max: " << sTp << "\n";

  sysTimePoint = std::chrono::system_clock::now();
  tp = std::chrono::system_clock::to_time_t(sysTimePoint);
  sTp = std::asctime(std::gmtime(&tp));
  std::cout << "Time now: " << sTp << "\n";
}