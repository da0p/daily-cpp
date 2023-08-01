#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>

template<typename T>
void
printRatio()
{
  std::cout << " precision: " << T::num << "/" << T::den << " second "
            << "\n";
  using MillSec = std::ratio_multiply<T, std::kilo>::type;
  using MicroSec = std::ratio_multiply<T, std::mega>::type;
  std::cout << std::fixed;
  std::cout << static_cast<double>(MillSec::num) / MillSec::den
            << " milliseconds "
            << "\n";
  std::cout << static_cast<double>(MicroSec::num) / MicroSec::den
            << " microseconds "
            << "\n";
}

int
main(int argc, char* argv[])
{
  std::cout << std::boolalpha << "\n";
  std::cout << "std::chrono::system_clock: "
            << "\n";
  printRatio<std::chrono::system_clock::period>();
  std::cout << "\n";

  std::cout << "std::chrono::steady_clock: "
            << "\n";
  std::cout << " is steady: " << std::chrono::steady_clock::is_steady << "\n";
  printRatio<std::chrono::steady_clock::period>();
  std::cout << "\n";

  std::cout << "std::chrono::high_resolution_clock: "
            << "\n";
  std::cout << " is steady: " << std::chrono::high_resolution_clock::is_steady
            << "\n";
  printRatio<std::chrono::high_resolution_clock::period>();
  std::cout << "\n";
}