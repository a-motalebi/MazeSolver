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
    std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
    Maze m(3, 3);
    char c {};
    //gaming mode while
    while (c != 'e' && c != 'E') {
        std::cin >> c;
        std::cin.ignore();
        switch (c) {
        case 'w':
        case 'W':
            if (m.player_plc->neighbors[Cell::U])
                m.player_plc = m.player_plc->neighbors[Cell::U];
            break;
        case 'a':
        case 'A':
            if (m.player_plc->neighbors[Cell::L])
                m.player_plc = m.player_plc->neighbors[Cell::L];
            break;
        case 'd':
        case 'D':
            if (m.player_plc->neighbors[Cell::R])
                m.player_plc = m.player_plc->neighbors[Cell::R];
            break;
        case 's':
        case 'S':
            if (m.player_plc->neighbors[Cell::D])
                m.player_plc = m.player_plc->neighbors[Cell::D];
            break;
        default:
            break;
        }
        std::cout << "\033[2J\033[1;1H"; //it clears the screen
        std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;

        m.printMaze();
    }

    return 0;
}
