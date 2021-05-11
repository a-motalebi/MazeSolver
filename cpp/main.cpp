#include "ansi.h"
#include "cell.h"
#include "maze.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main(int agrc, char** argv)
{

    unsigned seed(time(nullptr));
    srand(seed);
    size_t w {}, h {};
    std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
    std::cout << print_as_color<ansi_color_code::magenta>("\t\t\t\t─▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄\n\t\t\t\t█░░░█░░░░░░░░░░▄▄░██░█\n\t\t\t\t█░▀▀█▀▀░▄▀░▄▀░░▀▀░▄▄░█\n\t\t\t\t█░░░▀░░░▄▄▄▄▄░░██░▀▀░█\n\t\t\t\t─▀▄▄▄▄▄▀─────▀▄▄▄▄▄▄▀\n") << std::endl;
    std::cout << print_as_color<ansi_color_code::blue>("Please input dimansions:\nwidth:");
    std::cin >> w;
    std::cout << print_as_color<ansi_color_code::blue>("height:");
    std::cin >> h;
    Maze m(w, h);
    m.printMaze();
    m.gameMode();
    return 0;
}
