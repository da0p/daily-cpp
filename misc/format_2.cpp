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
  enum class IndexFormat
  {
    Normal,
    Short,
    WithPlus
  };

  bool localized = false;

  IndexFormat indexFormat{IndexFormat::Normal};

  constexpr auto parse(std::format_parse_context& ctx)
  {
    auto it = ctx.begin();
    auto end = ctx.end();

    auto isChar = [&](char c) {
      if((it != ctx.end()) && (*it == c)) {
        ++it;
        return true;
      }
      return false;
    };

    if(isChar('L')) {
      localized = true;
    }

    if(isChar('s')) {
      indexFormat = IndexFormat::Short;
    } else if(isChar('p')) {
      indexFormat = IndexFormat::WithPlus;
    }

    if(it != end && *it != '}') {
      throw format_error("Invalid format");
    }

    return it;
  }

  auto format(StockIndex const& index, std::format_context& ctx) const
  {
    auto const locFloat{localized ? "L"s : ""s};
    auto const plus{(IndexFormat::WithPlus == indexFormat) ? "+"s : ""s};

    if(IndexFormat::Short == indexFormat) {
      auto const fmt = std::format("{{:10}} {{:>8.2{}f}}", locFloat);
      return std::vformat_to(
        ctx.out(), fmt, std::make_format_args(index.name(), index.points())
      );
    } else {
      auto const fmt{std::format(
        "{{:10}} {{:>8.2{0}f}}  {{:>{1}7.2{0}f}}  {{:{1}.2{0}f}}%",
        locFloat,
        plus
      )};

      return std::vformat_to(
        ctx.out(),
        fmt,
        std::make_format_args(
          index.name(),
          index.points(),
          index.pointsDiff(),
          index.pointsPercent()
        )
      );
    }
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
  std::cout << "\n\n";
  for(auto const& index : stockIndex) {
    std::cout << std::format("{:s}\n", index);
  }
  std::cout << "\n\n";
  for(auto const& index : stockIndex) {
    std::cout << std::format("{:p}\n", index);
  }
}