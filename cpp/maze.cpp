#include "maze.h"
#include "ansi.h"
#include <algorithm>
Maze::Maze(size_t w, size_t h)
    : w { w }
    , h { h }
{
    totalCells = w * h;
    VisCells = 0; //the number of visited Cells
    generateGrid();
    randStart();
    walk();
}

void Maze::generateGrid()
{
    size_t i = 0;
    for (size_t y {}; y < h; y++) {
        for (size_t x {}; x < w; x++) {
            grid.emplace_back(x, y, i);
            i++;
        }
    }
    player_plc = &grid[0];
}
// selects random starting point
void Maze::randStart()
{
    curCell = &grid[rand() % totalCells];
    curCell->setVisited();
    VisCells++;
    visCells.push_back(curCell->getIndex());
}
void Maze::walk()
{
    // std::cout << "WALK\n";
    // printMaze();
    Cell* nextCell = nextStep();
    // std::cout << nextCell->getIndex() << std::endl;
    // Build path between the curCell and nextCell if nextCell is not null
    if (nextCell != nullptr) {
        // std::cout << "FIRST mode\n";
        curCell->updatePaths(nextCell);
        // curCell->setVisited();
        curCell = nextCell;
        curCell->setVisited();
        VisCells++;
        visCells.push_back(curCell->getIndex());
        walk();
        // std::cout << "FIRST mode2\n";
    } else {
        // std::cout << "hunt mode\n";
        // Enter Hunt Mode
        // Find a random previously visited Cell, make it the current Cell, & start a new path from it
        if (VisCells < totalCells && !visCells.empty()) {
            for (auto& i : grid) {
                if (!i.isVisited()) {
                    std::vector<Cell*> nofn;
                    if (i.getIndex() != w * h - 1)
                        if (&grid[i.getIndex() + 1]) {
                            if (grid[i.getIndex() + 1].isVisited())
                                nofn.push_back(&grid[i.getIndex() + 1]);
                        }
                    if (i.getIndex())
                        if (&grid[i.getIndex() - 1]) {
                            if (grid[i.getIndex() - 1].isVisited())
                                nofn.push_back(&grid[i.getIndex() - 1]);
                        }
                    if (i.getIndex() < w * h - w)
                        if (&grid[i.getIndex() + w]) {
                            if (grid[i.getIndex() + w].isVisited())
                                nofn.push_back(&grid[i.getIndex() + w]);
                        }
                    if (i.getIndex() >= w)
                        if (&grid[i.getIndex() - w]) {
                            if (grid[i.getIndex() - w].isVisited())
                                nofn.push_back(&grid[i.getIndex() - w]);
                        }
                    if (nofn.size()) {
                        std::random_shuffle(nofn.begin(), nofn.end());
                        curCell = nofn.back();
                        std::remove(visCells.begin(), visCells.end(), curCell->getIndex());
                        // VisCells--;
                        walk();
                    }
                }
            }
            // std::random_shuffle(visCells.begin(), visCells.end());
            // int index = visCells.back();
            // curCell = &grid[index];
            // visCells.pop_back();
            // VisCells--;
            // walk();
        } else {
            // if all Cells have been visited then the maze is complete - print it!
            printMaze();
        }
    }
}
// Finds a random unvisited neighbor square and returns it. Returns a nullptr if all neighbors have been visited
Cell* Maze::nextStep()
{
    std::vector<Cell*> notVisited;
    int x = curCell->getX();
    int y = curCell->getY();
    size_t index[4] = { getIndex(x, y - 1), getIndex(x, y + 1), getIndex(x - 1, y), getIndex(x + 1, y) };
    if (y - 1 >= 0 && !grid[index[0]].isVisited())
        notVisited.push_back(&grid[index[0]]);
    if (y + 1 < static_cast<int>(h) && !grid[index[1]].isVisited())
        notVisited.push_back(&grid[index[1]]);
    if (x - 1 >= 0 && !grid[index[2]].isVisited())
        notVisited.push_back(&grid[index[2]]);
    if (x + 1 < static_cast<int>(w) && !grid[index[3]].isVisited())
        notVisited.push_back(&grid[index[3]]);
    if (!notVisited.empty())
        return notVisited[rand() % notVisited.size()];
    else
        return nullptr;
}
void Maze::printMaze()
{
    size_t i {};
    for (size_t y {}; y <= h; y++) {
        for (size_t x {}; x < w; x++) {
            if (x == 0)
                std::cout << print_as_color<ansi_color_code::blue>("  ▄ ");
            if (y == 0)
                std::cout << print_as_color<ansi_color_code::blue>("▄ ▄ ");
            else if (grid[i].neighbors[Cell::R] == nullptr && &grid[i] == player_plc) {
                std::cout << print_as_color<ansi_color_code::red>("웃");
                std::cout << print_as_color<ansi_color_code::blue>("▄ ");
            } else if (grid[i].neighbors[Cell::R] == nullptr)
                std::cout << print_as_color<ansi_color_code::blue>("  ▄ ");
            else if (&grid[i] == player_plc) {
                std::cout << print_as_color<ansi_color_code::red>("웃");
                std::cout << print_as_color<ansi_color_code::blue>("  ");
            } else
                std::cout << "    ";
            if (y > 0)
                i++;
        }
        if (y != 0) {
            for (size_t x {}; x < w; x++)
                if (y > 0)
                    i--;
            std::cout << std::endl;
            for (size_t x {}; x < w; x++) {
                if (x == 0)
                    std::cout << print_as_color<ansi_color_code::blue>("  ▄ ");
                if (grid[i].neighbors[Cell::D] == nullptr)
                    std::cout << print_as_color<ansi_color_code::blue>("▄ ▄ ");
                else
                    std::cout << print_as_color<ansi_color_code::blue>("  ▄ ");
                if (y > 0)
                    i++;
            }
        }
        std::cout << std::endl;
    }
}