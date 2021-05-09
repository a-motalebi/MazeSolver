#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>
class Cell {
private:
    size_t x, y, ind;
    bool visited;

public:
    std::vector<Cell*> neighbors { 4, nullptr }; //nullptr if not connected or wall
    enum directions : size_t {
        U = 0,
        D = 1,
        L = 2,
        R = 3
    };
    Cell(size_t x, size_t y, size_t ind);
    void setVisited() { visited = true; };
    void setNotVisited() { visited = false; };
    size_t getIndex() const { return ind; };
    size_t getX() const { return x; };
    size_t getY() const { return y; };
    bool isVisited() const { return visited; };
    void updatePaths(Cell* next);
};

#endif