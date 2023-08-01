#include <chrono>
#include <iomanip>
#include <iostream>

template<typename T>
void
durationSinceEpoch(const T dur)
{
  std::cout << " Counts since epoch: " << dur.count() << "\n";
  using MyMinuteTick = std::chrono::duration<double, std::ratio<60>>;
  const MyMinuteTick myMinute(dur);
  std::cout << std::fixed;
  std::cout << " Minutes since epoch: " << myMinute.count() << "\n";
  using MyYearTick =
    std::chrono::duration<double, std::ratio<60 * 60 * 24 * 365>>;
  const MyYearTick myYear(dur);
  std::cout << " Years since epoch: " << myYear.count() << "\n";
}

int
main(int argc, char* argv[])
{
  std::chrono::system_clock::time_point timeNowSysClock =
    std::chrono::system_clock::now();
  std::chrono::system_clock::duration timeDurSysClock =
    timeNowSysClock.time_since_epoch();
  durationSinceEpoch(timeDurSysClock);

  std::cout << "\n";

  auto const timeNowHiRes = std::chrono::high_resolution_clock::now();
  auto const timeDurHiResClock = timeNowHiRes.time_since_epoch();
  std::cout << "high_resolution_clock: "
            << "\n";
  durationSinceEpoch(timeDurHiResClock);
}