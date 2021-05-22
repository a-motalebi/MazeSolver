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
    std::cout << print_as_color<ansi_color_code::blue>("Please enter dimansions:\nwidth:");
    std::cin >> w;
    std::cout << print_as_color<ansi_color_code::blue>("height:");
    std::cin >> h;
    Maze m(w, h);
    m.printMaze();
    std::cout << std::endl;
    char c { 'm' };
    while (c != 'e' && c != 'E') {
        if (c == 'M' || c == 'm')
            m.mainMenu();
        std::cout << print_as_color<ansi_color_code::blue>("Please enter \"m\" to return to the main menu or \"e\" to exit.") << std::endl;
        std::cin >> c;
    }

    return 0;
}
