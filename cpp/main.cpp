#include "ansi.h"
#include "cell.h"
#include "maze.h"
#include <iostream>

int main(int agrc, char** argv)
{

    unsigned seed(time(nullptr));
    srand(seed);
    size_t w {}, h {};
    char c { 'm' };
    do {
        std::cout << "\033[2J\033[1;1H"; //it clears the screen

        std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
        std::cout << print_as_color<ansi_color_code::magenta>("\t\t\t\t─▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄\n\t\t\t\t█░░░█░░░░░░░░░░▄▄░██░█\n\t\t\t\t█░▀▀█▀▀░▄▀░▄▀░░▀▀░▄▄░█\n\t\t\t\t█░░░▀░░░▄▄▄▄▄░░██░▀▀░█\n\t\t\t\t─▀▄▄▄▄▄▀─────▀▄▄▄▄▄▄▀\n") << std::endl;
        std::cout << print_as_color<ansi_color_code::blue>("Please enter dimansions:\nwidth:");
        std::cin >> w;
        std::cout << print_as_color<ansi_color_code::blue>("height:");
        std::cin >> h;
        if (w * h < 2) {
            c = 'n';
            continue;
        }
        Maze m(w, h);
        m.printMaze();
        std::cout << std::endl;
        while (c != 'e' && c != 'E') {
            if (c == 'M' || c == 'm')
                m.mainMenu();
            std::cout << print_as_color<ansi_color_code::blue>("Please enter \"m\" to return to the main menu,\"n\" to create a new maze or \"e\" to exit.") << std::endl;
            std::cin >> c;
            if (c == 'n' || c == 'N')
                break;
        }
    } while (c == 'n' || c == 'N');
    return 0;
}
