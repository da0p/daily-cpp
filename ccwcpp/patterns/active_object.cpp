#include <algorithm>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <utility>
#include <vector>

class IsPrime
{
public:
  std::pair<bool, int> operator()(int i)
  {
    for(int j = 2; j * j <= i; ++j) {
      if(i % j == 0) {
        return std::make_pair(false, i);
      }
    }
    return std::make_pair(true, i);
  }
};

class ActiveObject
{

private:
  bool runNextTask()
  {
    std::lock_guard<std::mutex> lockGuard(mActivationListMutex);
    auto empty = mActivationList.empty();
    if(!empty) {
      auto myTask = std::move(mActivationList.front());
      mActivationList.pop_front();
      myTask.first(myTask.second);
    }
    return empty;
  }
  std::deque<std::pair<std::packaged_task<std::pair<bool, int>(int)>, int>>
    mActivationList;
  std::mutex mActivationListMutex;

public:
  std::future<std::pair<bool, int>> enqueueTask(int i)
  {
    IsPrime isPrime;
    std::packaged_task<std::pair<bool, int>(int)> newJob(isPrime);
    auto isPrimeFuture = newJob.get_future();
    auto pair = std::make_pair(std::move(newJob), i);
    {
      std::lock_guard<std::mutex> lockGuard(mActivationListMutex);
      mActivationList.push_back(std::move(pair));
    }

    return isPrimeFuture;
  }

  void run()
  {
    std::vector<std::jthread> allServants;
    // only one thread because the activation list is the bottleneck
    for(int n = 0; n < 1; ++n) {
      allServants.emplace_back([this] {
        while(!runNextTask())
          ;
      });
    }
  }
};

std::vector<int>
getRandNumbers(int number)
{
  std::random_device seed;
  std::mt19937 engine(seed());
  std::uniform_int_distribution<> dist(1000000, 1000000000);
  std::vector<int> numbers;

  for(long long i = 0; i < number; ++i) {
    numbers.push_back(dist(engine));
  }

  return numbers;
}

std::future<std::vector<std::future<std::pair<bool, int>>>>
getFutures(ActiveObject& activeObject, int numberPrimes)
{
  return std::async([&activeObject, numberPrimes] {
    std::vector<std::future<std::pair<bool, int>>> futures;
    auto randNumbers = getRandNumbers(numberPrimes);
    for(auto numb : randNumbers) {
      futures.push_back(activeObject.enqueueTask(numb));
    }
    return futures;
  });
}

int
main(int argc, char* argv[])
{
  ActiveObject activeObject;

  auto client1 = getFutures(activeObject, 1998);
  auto client2 = getFutures(activeObject, 2003);
  auto client3 = getFutures(activeObject, 2011);
  auto client4 = getFutures(activeObject, 2014);
  auto client5 = getFutures(activeObject, 2017);

  auto futures1 = client1.get();
  auto futures2 = client2.get();
  auto futures3 = client3.get();
  auto futures4 = client4.get();
  auto futures5 = client5.get();

  // put all futures together
  futures1.insert(
    futures1.end(),
    std::make_move_iterator(futures2.begin()),
    std::make_move_iterator(futures2.end())
  );

  futures1.insert(
    futures1.end(),
    std::make_move_iterator(futures3.begin()),
    std::make_move_iterator(futures3.end())
  );

  futures1.insert(
    futures1.end(),
    std::make_move_iterator(futures4.begin()),
    std::make_move_iterator(futures4.end())
  );

  futures1.insert(
    futures1.end(),
    std::make_move_iterator(futures5.begin()),
    std::make_move_iterator(futures5.end())
  );

  activeObject.run();

  // get the results from the futures
  std::vector<std::pair<bool, int>> futResults;
  futResults.reserve(futures1.size());
  for(auto& fut : futures1) {
    futResults.push_back(fut.get());
  }

  std::sort(futResults.begin(), futResults.end());

  // separate the primes from the non-primes
  auto prIt = std::find_if(
    futResults.begin(),
    futResults.end(),
    [](std::pair<bool, int> pa) { return pa.first == true; }
  );

  std::cout << "Number primes: " << std::distance(prIt, futResults.end())
            << "\n";
  std::cout << "Primes: "
            << "\n";
  std::for_each(prIt, futResults.end(), [](auto p) {
    std::cout << p.second << " ";
  });

  std::cout << "\n\n";
  std::cout << "Number no primes: " << std::distance(futResults.begin(), prIt)
            << "\n";
  std::cout << "No primes: "
            << "\n";
  std::for_each(futResults.begin(), prIt, [](auto p) {
    std::cout << p.second << " ";
  });
}