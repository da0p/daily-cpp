#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int
main()
{
  alignas(alignof(std::string)) char buff1[sizeof(std::string) * 5];
  alignas(alignof(std::string)) char buff2[sizeof(std::string) * 5];
  std::vector<std::string> data = {"hello", "world", "and", "everyone", "else"};

  // The main benegit of using the uninitialized memory algorithms is that
  // they corretly handle transactional behavior. Transactionality is important
  // in cases where the constructor of an object can throw. If one of the
  // objects fails to construct, the algorithms will correctly roll back by
  // destructing already constructed objects.
  auto* bg1 = reinterpret_cast<std::string*>(buff1);
  std::uninitialized_copy(data.begin(), data.end(), bg1);
  for(auto i = 0; i < 5; i++) {
    std::cout << bg1[i] << " ";
  }
  std::destroy_n(bg1, 5);

  std::cout << "\n\n";
  auto* bg2 = reinterpret_cast<std::string*>(buff2);
  std::uninitialized_move(data.begin(), data.end(), bg2);
  for(auto i = 0; i < 5; i++) {
    std::cout << bg2[i] << " ";
  }
  std::destroy_n(bg2, 5);
}