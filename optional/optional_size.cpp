#include <iostream>
#include <optional>

// optional wraps your type, prepares space for it and then adds one boolean
// parameter. It will extend the size of your type according to the alignment
// rules

/*
template<typename T>
class optional
{
    bool _initialized;
    std::aligned_storage_t<sizeof(t), alignof(T)> _storage;
public:
    // operations
}
*/

struct RangeOpt
{
  std::optional<double> mMin;
  std::optional<double> mMax;
};

struct Range
{
  bool mMinAvailable;
  bool mMaxAvailable;
  double mMin;
  double mMax;
};

int
main()
{
  std::cout << "RangeOpt's size = " << sizeof(RangeOpt) << "\n";
  std::cout << "Range's size = " << sizeof(Range) << "\n";
}