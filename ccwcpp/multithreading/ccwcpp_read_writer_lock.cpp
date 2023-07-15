#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <shared_mutex>
#include <string>
#include <thread>

std::map<std::string, int> teleBook{
  {"Dijkstra", 1972},
  {"Scott", 1976},
  {"Ritchie", 1983}};

std::shared_timed_mutex teleBookMutex;

void
addToTeleBook(std::string const& na, int tele)
{
  std::lock_guard<std::shared_timed_mutex> writerLock(teleBookMutex);
  std::cout << "\nStarting Update...." << na;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  teleBook[na] = tele;
  std::cout << " ... Ending Update ..." << na << "\n";
}

void
printNumber(std::string const& na)
{
  std::shared_lock<std::shared_timed_mutex> readerLock(teleBookMutex);
  auto searchEntry = teleBook.find(na);
  if(searchEntry != teleBook.end()) {
    std::cout << searchEntry->first << ": " << searchEntry->second << "\n";
  } else {
    std::cout << na << " not found!"
              << "\n";
  }
}

int
main(int argc, char* argv[])
{
  std::thread reader1([] { printNumber("Scott"); });
  std::thread reader2([] { printNumber("Ritchie"); });
  std::thread w1([] { addToTeleBook("Scott", 1968); });
  std::thread reader3([] { printNumber("Dijkstra"); });
  std::thread reader4([] { printNumber("Scott"); });
  std::thread w2([] { addToTeleBook("Bjarne", 1965); });
  std::thread reader5([] { printNumber("Scott"); });
  std::thread reader6([] { printNumber("Ritchie"); });
  std::thread reader7([] { printNumber("Scott"); });
  std::thread reader8([] { printNumber("Bjarne"); });

  reader1.join();
  reader2.join();
  reader3.join();
  reader4.join();
  reader5.join();
  reader6.join();
  reader7.join();
  reader8.join();
  w1.join();
  w2.join();

  std::cout << "\n\nThe new telephone book"
            << "\n";
  for(auto teleIt : teleBook) {
    std::cout << teleIt.first << ": " << teleIt.second << "\n";
  }
  std::cout << "\n";

  return EXIT_SUCCESS;
}