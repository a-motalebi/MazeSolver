#include "ansi.h"

void load_bar()
{
    //print a colored progress bar using ANSI escape codes
    float progress = 0.0;
    while (progress <= 1.0) {
        int barWidth = 40;

        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; i++) {
            if (i < pos)
                std::cout << print_as_color<ansi_color_code::red>("=");
            else if (i == pos)
                std::cout << print_as_color<ansi_color_code::yellow>(">");
            else
                std::cout << " ";
        }
        std::cout << "] " << print_as_color<ansi_color_code::blue>(int(progress * 100.0)) << " %";
        std::cout.flush();
        if (progress <= 0.99)
            std::cout << "\033[2J\033[1;1H"; //it clears the screen
        progress += 0.01; // for demonstration only
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    std::cout << std::endl;
}