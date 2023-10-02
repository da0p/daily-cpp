#include <charconv>
#include <iostream>
#include <map>
#include <optional>
#include <variant>

class CmdLine
{
public:
  using Arg = std::variant<int, std::string>;
  explicit CmdLine(int argc, char const** argv) { ParseArgs(argc, argv); }

  std::optional<Arg> find(std::string const& name) const;

  void ParseArgs(int argc, char const** argv);

private:
  std::map<std::string, Arg> mParseArgs;
};

std::optional<CmdLine::Arg>
CmdLine::find(std::string const& name) const
{
  if(auto const it = mParseArgs.find(name); it != mParseArgs.end()) {
    return it->second;
  }

  return {};
}

CmdLine::Arg
tryParseString(std::string_view sv)
{
  // try with int first
  int iResult = 0;
  auto const last = sv.data() + sv.size();
  auto const res = std::from_chars(sv.data(), last, iResult);
  if(res.ec != std::errc{} || res.ptr != last) {
    // if not possible, then just asume it's a string
    return std::string(sv.data(), sv.size());
  }
  return iResult;
}

void
CmdLine::ParseArgs(int argc, char const** argv)
{
  for(int i = 1; i < argc; i += 2) {
    if(argv[i][0] != '-') {
      throw std::runtime_error("wrong command name");
    }
    mParseArgs[argv[i] + 1] = tryParseString(argv[i + 1]);
  }
}

int
main(int argc, char const** argv)
{
  if(argc == 1) {
    std::cout << "run with -paramInt 10 -paramTex \"Hello World\"\n";
    return 0;
  }

  try {
    CmdLine cmdLine(argc, argv);

    if(auto arg = cmdLine.find("paramInt"); arg) {
      std::cout << "paramInt is " << std::get<int>(*arg) << "\n";
    }

    if(auto arg = cmdLine.find("paramTex"); arg) {
      std::cout << "paramTex is " << std::get<std::string>(*arg) << "\n";
    }
  } catch(std::bad_variant_access& err) {
    std::cerr << "...err: accessing a wrong variant type, " << err.what()
              << "\n";
  } catch(std::runtime_error& err) {
    std::cerr << "...err: " << err.what() << "\n";
  }

  return 0;
}