#include <chrono>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>

enum class ansi_color_code : int {
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37,
};

template <typename printable>
std::string print_as_color(printable const& value, ansi_color_code color)
{
    std::stringstream sstr;
    sstr << "\033[1;" << static_cast<int>(color) << "m" << value << "\033[0m";
    return sstr.str();
}
template <ansi_color_code color, typename printable>
std::string print_as_color(printable const& value)
{
    std::stringstream sstr;
    sstr << "\033[1;" << static_cast<int>(color) << "m" << value << "\033[0m";
    return sstr.str();
}
void load_bar();
