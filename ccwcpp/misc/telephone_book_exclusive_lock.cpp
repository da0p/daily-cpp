#include <chrono>
#include <cstdlib>
#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <mutex>
#include <random>
#include <regex>
#include <shared_mutex>
#include <sstream>
#include <unordered_map>
#include <vector>

using TeleBookMap = std::unordered_map<std::string, int>;

class TeleBook
{
private:
  mutable std::mutex mTeleBookMutex;
  mutable TeleBookMap mTeleBook;

  std::vector<std::string> getRandomNames(TeleBookMap const& teleBook)
  {
    std::vector<std::string> allNames;
    for(auto const& pair : teleBook) {
      allNames.push_back(pair.first);
    }
    std::random_device randDev;
    std::mt19937 generator(randDev());
    std::shuffle(allNames.begin(), allNames.end(), generator);

    return allNames;
  }
  void
  getNumbers(std::vector<std::string> const& randomNames, TeleBook& teleBook)
  {
    for(auto const& name : randomNames) {
      teleBook.getNumber(name);
    }
  }

public:
  TeleBook(TeleBookMap const& teleBook)
    : mTeleBook(teleBook)
  {
  }
  TeleBookMap get() const
  {
    std::lock_guard<std::mutex> lockTele(mTeleBookMutex);
    return mTeleBook;
  }
  int getNumber(std::string const& name) const
  {
    std::lock_guard<std::mutex> lockTele(mTeleBookMutex);
    return mTeleBook[name];
  }
  void setNewNumber(std::string const& name)
  {
    std::lock_guard<std::mutex> lockTele(mTeleBookMutex);
    mTeleBook[name]++;
  }
};

std::vector<std::string>
getRandomNames(TeleBookMap const& teleBook)
{
  std::vector<std::string> allNames;
  for(auto const& pair : teleBook) {
    allNames.push_back(pair.first);
  }
  std::random_device randDev;
  std::mt19937 generator(randDev());

  std::shuffle(allNames.begin(), allNames.end(), generator);

  return allNames;
}

void
getNumbers(std::vector<std::string> const& randomNames, TeleBook& teleBook)
{
  for(auto const& name : randomNames) {
    teleBook.getNumber(name);
  }
}

int
main()
{
  TeleBookMap book{
    {"John", 1122334455}, {"Alex", 2929292929}, {"Jana", 1234567890}};
  TeleBook teleBook(book);
  std::vector<std::string> allNames = getRandomNames(teleBook.get());
  std::vector<std::string> tenthOfAllNames(
    allNames.begin(), allNames.begin() + allNames.size() / 10
  );
  auto start = std::chrono::steady_clock::now();

  std::vector<std::future<void>> futReaders{10};

  for(auto& futReader : futReaders) {
    futReader = std::move(std::async(std::launch::async, [&] {
      getNumbers(allNames, teleBook);
    }));
  }

  auto futWriter = std::async(std::launch::async, [&] {
    for(const auto& name : tenthOfAllNames) {
      teleBook.setNewNumber(name);
    }
  });

  for(auto& futReader : futReaders) {
    futReader.get();
  }

  std::chrono::duration<double> duration =
    std::chrono::steady_clock::now() - start;

  std::cout << "Process time: " << duration.count() << " seconds"
            << "\n";

  return EXIT_SUCCESS;
}