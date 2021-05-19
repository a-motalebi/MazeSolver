#ifndef MAZE_H
#define MAZE_H
#include "cell.h"
#include "graph.h"
#include <iostream>
#include <vector>
class Maze {
private:
    size_t w, h;
    std::vector<Cell> grid;
    std::vector<size_t> visCells; //Cells that have been visited - used in Hunt Mode
    Graph::Node* curNode;
    Cell* curCell {}; //pointer to the current Cell
    size_t totalCells; //total number of Cells in the maze
    size_t VisCells; //count of visited Cells

public:
    std::vector<size_t> notInserted;
    Graph graph {};
    Cell* player_plc;
    Cell* goal_plc;
    Maze(size_t w, size_t h);
    void generateGrid();
    void randStart();
    Cell* nextStep();
    void walk();
    size_t getIndex(size_t x, size_t y) const { return y * w + x; };
    void printMaze();
    void gameMode();
    void setGraph();
    void insert(size_t);
    void BFS();
    void preorder(Graph::Node*);
    void postorder(Graph::Node*);
    void setNodesNotChecked();
};

#endif
