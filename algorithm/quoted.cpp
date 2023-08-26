#include <iomanip>
#include <iostream>
#include <sstream>

void
default_delimiter()
{
  const std::string in = "This is a quoted string \"hola\"";
  std::stringstream ss;
  ss << std::quoted(in);
  std::string out;
  ss >> std::quoted(out);

  std::cout << "Default limiter case:\n"
               "read in ["
            << in
            << "]\n"
               "stored as ["
            << ss.str()
            << "]\n"
               "written out ["
            << out << "]\n\n";
}

void
custom_delimiter()
{
  char const delim{'$'};
  char const escape{'%'};

  const std::string in = "This is a quoted string $quotes$ $too";
  std::stringstream ss;
  ss << std::quoted(in, delim, escape);
  std::string out;
  ss >> std::quoted(out, delim, escape);

  std::cout << "Custom delimiter case:\n"
               "read in ["
            << in
            << "]\n"
               "stored as ["
            << ss.str()
            << "]\n"
               "written out ["
            << out << "]\n\n";
}

int
main(int argc, char* argv[])
{
  default_delimiter();
  custom_delimiter();

  return 0;
}