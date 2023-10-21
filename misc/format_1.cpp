#include <format>
#include <iostream>
#include <vector>

class StockIndex
{
private:
  std::string mName{};
  double mLastPoints{};
  double mPoints{};

public:
  StockIndex(std::string name)
    : mName{name}
  {
  }

  std::string const& name() const { return mName; }

  void setPoints(double points)
  {
    mLastPoints = mPoints;
    mPoints = points;
  }

  double points() const { return mPoints; }

  double pointsDiff() const { return mPoints - mLastPoints; }

  double pointsPercent() const
  {
    if(0.0 == mLastPoints) {
      return 0.0;
    }
    return (mPoints - mLastPoints) / mLastPoints * 100.0;
  }
};

template<>
struct std::formatter<StockIndex>
{
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  auto format(StockIndex const& index, format_context& ctx) const
  {
    return std::format_to(
      ctx.out(),
      "{:10}  {:>8.2f}  {:>6.2f} {:>10.2f}%",
      index.name(),
      index.points(),
      index.pointsDiff(),
      index.pointsPercent()
    );
  }
};

int
main()
{
  std::vector<StockIndex> stockIndex;

  StockIndex google{"Google"};
  google.setPoints(20.20);
  google.setPoints(40.40);
  stockIndex.emplace_back(google);

  StockIndex apple{"Apple"};
  apple.setPoints(42.20);
  apple.setPoints(50.50);
  stockIndex.emplace_back(apple);

  for(auto const& index : stockIndex) {
    std::cout << std::format("{}\n", index);
  }

  return 0;
}
