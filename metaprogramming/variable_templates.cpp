#include <iostream>

/**
 * @note: Variable templates allow us to define variables that are templates
 * either at namespace scope, in which case they represent a family of global
 * variables, or at class scope, in which case they represent static data
 * members.
 *
 */

// Not a nice way of writing it
template<typename T>
struct PI_X
{
  static const T value;
};

template<typename T>
const T PI_X<T>::value = T(3.1415926535897932385L);

template<typename T>
T
sphere_volume_X(T const r)
{
  return 4 * PI_X<T>::value * r * r * r / 3;
}

// Better way of writing
template<typename T>
constexpr T PI = T(3.1415926535897932385L);

template<typename T>
T
sphere_volume(T const r)
{
  return 4 * PI<T> * r * r * r / 3;
}

// Another example of explicit specialization of variable templates.
template<typename T>
constexpr T SEPARATOR = '\n';

template<>
constexpr wchar_t SEPARATOR<wchar_t> = L'\n';

template<typename T>
std::basic_ostream<T>&
show_parts(std::basic_ostream<T>& s, std::basic_string_view<T> const& str)
{
  using size_type = typename std::basic_string_view<T>::size_type;
  size_type start = 0;
  size_type end;
  do {
    end = str.find(SEPARATOR<T>, start);
    s << '[' << str.substr(start, end - start) << ']' << SEPARATOR<T>;
    start = end + 1;
  } while(end != std::string::npos);

  return s;
}

// variable templates can be members of classes
struct math_constants
{
  template<typename T>
  static constexpr T PI = T(3.1415926535897932385L);
};

template<typename T>
T
sphere_volume_Y(T const r)
{
  return 4 * math_constants::PI<T> * r * r * r / 3;
}

// A variable template can be declared in a class and then provide its
// definition outside the class
//
// struct math_consts
// {
//   template<class T>
//   static const T PI;
// }
//
// template<class T>
// const T math_constants::PI = T(3.1415926535897932385L);

int
main(int argc, char* argv[])
{
  std::cout << "Volume_1 = " << sphere_volume_X(11.0f) << "\n";
  // Without the use of template, this line will have a warning while
  // compiling
  std::cout << "Volume_2 = " << sphere_volume(10.0f) << "\n";

  show_parts<char>(std::cout, "one\ntwo\nthree");
  show_parts<wchar_t>(std::wcout, L"one line");

  std::cout << "Volume_3 = " << sphere_volume_Y(12.0f) << "\n";
}