#ifndef MAZE_H
#define MAZE_H
#include "cell.h"
#include <iostream>
#include <vector>

class Maze {
private:
    size_t w, h;
    std::vector<Cell> grid;
    std::vector<size_t> visCells; //Cells that have been visited - used in Hunt Mode
    Cell* curCell {}; //pointer to the current Cell
    size_t totalCells; //total number of Cells in the maze
    size_t VisCells; //count of visited Cells

public:
    Cell* player_plc;
    Maze(size_t w, size_t h);
    void generateGrid();
    void randStart();
    Cell* nextStep();
    void walk();
    // Calculates and returns the vector index for a set of x,y coordinates
    size_t getIndex(size_t x, size_t y) const { return y * h + x; };
    void printMaze();
};

#endif
