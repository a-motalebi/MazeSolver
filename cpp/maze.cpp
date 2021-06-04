#include "maze.h"
#include "ansi.h"
#include <algorithm>
#include <memory>

Maze::Maze(size_t w, size_t h)
    : w { w }
    , h { h }
{
    totalCells = w * h;
    VisCells = 0; //the number of visited Cells
    generateGrid();
    randStart();
    walk();
    for (size_t i {}; i < totalCells; i++)
        notInserted.push_back(i);
    setGraph();
}

void Maze::generateGrid()
{
    size_t i {};
    for (size_t y {}; y < h; y++) {
        for (size_t x {}; x < w; x++) {
            grid.emplace_back(x, y, i);
            i++;
        }
    }
    std::cout << print_as_color<ansi_color_code::blue>("Please enter player position(0-") << print_as_color<ansi_color_code::blue>(w * h - 1) << print_as_color<ansi_color_code::blue>("):") << std::endl;
    std::cin >> i;
    player_plc = &grid[i];
    std::cout << print_as_color<ansi_color_code::blue>("Please enter goal position:(0-") << print_as_color<ansi_color_code::blue>(w * h - 1) << print_as_color<ansi_color_code::blue>("):") << std::endl;
    std::cin >> i;
    goal_plc = &grid[i];
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
    // printMaze();// show steps
    Cell* nextCell = nextStep();
    // Build path between the curCell and nextCell if nextCell is not null
    if (nextCell) {
        curCell->updatePaths(nextCell);
        curCell = nextCell;
        curCell->setVisited();
        VisCells++;
        visCells.push_back(curCell->getIndex());
        walk();
    } else {
        // Enter Hunting Mode
        // Find the first unvisited Cell that has visited neighbor, make it the current Cell, & start a new path from it
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
                        walk();
                    }
                }
            }
        }
    }
}
// Finds a random unvisited neighbor cell and returns it. Returns a nullptr if all neighbors have been visited
Cell* Maze::nextStep()
{
    std::vector<Cell*> notVisited;
    int x { static_cast<int>(curCell->getX()) };
    int y { static_cast<int>(curCell->getY()) };
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
                std::cout << print_as_color<ansi_color_code::blue>("  ■ ");
            if (goal_plc) {
                if (x == goal_plc->getX() && y == goal_plc->getY() + 1 && grid[i].neighbors[Cell::R] == nullptr) {
                    std::cout << print_as_color<ansi_color_code::green>("유");
                    std::cout << print_as_color<ansi_color_code::blue>("■ ");
                    i++;
                    continue;
                }
                if (x == goal_plc->getX() && y == goal_plc->getY() + 1 && graph.isInTree(grid[i].nodeOfCell, grid[i].neighbors[Cell::R]->nodeOfCell) && graph.isInTree(graph.lastChecked, grid[i].nodeOfCell)) {
                    std::cout << print_as_color<ansi_color_code::green>("유");
                    std::cout << print_as_color<ansi_color_code::red>("✔ ");
                    i++;
                    continue;
                }
                if (x == goal_plc->getX() && y == goal_plc->getY() + 1 && grid[i].nodeOfCell->isChecked() && grid[i].neighbors[Cell::R]->nodeOfCell->isChecked()) {
                    std::cout << print_as_color<ansi_color_code::green>("유");
                    std::cout << print_as_color<ansi_color_code::yellow>("✘ ");
                    i++;
                    continue;
                }
                if (x == goal_plc->getX() && y == goal_plc->getY() + 1) {
                    std::cout << print_as_color<ansi_color_code::green>("유");
                    std::cout << print_as_color<ansi_color_code::blue>("  ");
                    i++;
                    continue;
                }
            }
            if (y == 0)
                std::cout << print_as_color<ansi_color_code::blue>("■ ■ ");
            else if (grid[i].neighbors[Cell::R] == nullptr && &grid[i] == player_plc) {
                std::cout << print_as_color<ansi_color_code::red>("웃");
                std::cout << print_as_color<ansi_color_code::blue>("■ ");
            } else if (grid[i].neighbors[Cell::R] == nullptr && graph.isInTree(graph.lastChecked, grid[i].nodeOfCell)) {
                std::cout << print_as_color<ansi_color_code::red>("✔ ");
                std::cout << print_as_color<ansi_color_code::blue>("■ ");
            } else if (grid[i].neighbors[Cell::R] == nullptr && grid[i].nodeOfCell->isChecked()) {
                std::cout << print_as_color<ansi_color_code::yellow>("✘ ");
                std::cout << print_as_color<ansi_color_code::blue>("■ ");
            } else if (grid[i].neighbors[Cell::R] == nullptr)
                std::cout << print_as_color<ansi_color_code::blue>("  ■ ");
            else if (&grid[i] == player_plc && graph.isInTree(graph.lastChecked, player_plc->neighbors[Cell::R]->nodeOfCell)) {
                std::cout << print_as_color<ansi_color_code::red>("웃");
                std::cout << print_as_color<ansi_color_code::red>("✔ ");
            } else if (&grid[i] == player_plc && player_plc->neighbors[Cell::R]->nodeOfCell->isChecked()) {
                std::cout << print_as_color<ansi_color_code::red>("웃");
                std::cout << print_as_color<ansi_color_code::yellow>("✘ ");
            } else if (&grid[i] == player_plc) {
                std::cout << print_as_color<ansi_color_code::red>("웃");
                std::cout << print_as_color<ansi_color_code::blue>("  ");
            } else if (graph.isInTree(graph.lastChecked, grid[i].nodeOfCell) && graph.isInTree(graph.lastChecked, grid[i].neighbors[Cell::R]->nodeOfCell))
                std::cout << print_as_color<ansi_color_code::red>("✔ ✔ ");
            else if (graph.isInTree(graph.lastChecked, grid[i].nodeOfCell) && !graph.isInTree(graph.lastChecked, grid[i].neighbors[Cell::R]->nodeOfCell) && !grid[i].neighbors[Cell::R]->nodeOfCell->isChecked())
                std::cout << print_as_color<ansi_color_code::red>("✔   ");
            else if (graph.isInTree(graph.lastChecked, grid[i].nodeOfCell) && !graph.isInTree(graph.lastChecked, grid[i].neighbors[Cell::R]->nodeOfCell)) {
                std::cout << print_as_color<ansi_color_code::red>("✔ ");
                std::cout << print_as_color<ansi_color_code::yellow>("✘ ");
            } else if (grid[i].nodeOfCell->isChecked() && grid[i].neighbors[Cell::R]->nodeOfCell->isChecked())
                std::cout << print_as_color<ansi_color_code::yellow>("✘ ✘ ");
            else if (graph.isInTree(graph.lastChecked, grid[i].nodeOfCell))
                std::cout << print_as_color<ansi_color_code::red>("✔   ");
            else if (grid[i].nodeOfCell->isChecked())
                std::cout << print_as_color<ansi_color_code::yellow>("✘   ");
            else
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
                    std::cout << print_as_color<ansi_color_code::blue>("  ■ ");
                if (grid[i].neighbors[Cell::D] == nullptr)
                    std::cout << print_as_color<ansi_color_code::blue>("■ ■ ");
                else if (graph.isInTree(graph.lastChecked, grid[i].neighbors[Cell::D]->nodeOfCell) && graph.isInTree(graph.lastChecked, grid[i].nodeOfCell)) {
                    std::cout << print_as_color<ansi_color_code::red>("✔ ");
                    std::cout << print_as_color<ansi_color_code::blue>("■ ");
                } else if (grid[i].neighbors[Cell::D]->nodeOfCell->isChecked() && grid[i].nodeOfCell->isChecked()) {
                    std::cout << print_as_color<ansi_color_code::yellow>("✘ ");
                    std::cout << print_as_color<ansi_color_code::blue>("■ ");
                } else
                    std::cout << print_as_color<ansi_color_code::blue>("  ■ ");
                if (y > 0)
                    i++;
            }
        }
        std::cout << std::endl;
    }
}
void Maze::gameMode()
{
    char c {};
    Cell* temp { player_plc };
    //gaming mode while
    while (c != 'e' && c != 'E') {
        std::cout << "\033[2J\033[1;1H"; //it clears the screen
        std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
        std::cout << print_as_color<ansi_color_code::blue>("You are the red one. Let's go find your friend!") << std::endl;
        std::cout << print_as_color<ansi_color_code::blue>("Please use \"w a s d\" to move. Or \"e\" to exit.") << std::endl;
        printMaze();
        std::cin >> c;
        switch (c) {
        case 'w':
        case 'W':
            if (player_plc->neighbors[Cell::U])
                player_plc = player_plc->neighbors[Cell::U];
            break;
        case 'a':
        case 'A':
            if (player_plc->neighbors[Cell::L])
                player_plc = player_plc->neighbors[Cell::L];
            break;
        case 'd':
        case 'D':
            if (player_plc->neighbors[Cell::R])
                player_plc = player_plc->neighbors[Cell::R];
            break;
        case 's':
        case 'S':
            if (player_plc->neighbors[Cell::D])
                player_plc = player_plc->neighbors[Cell::D];
            break;
        case 'e':
        case 'E':
            player_plc = temp;

            break;
        default:
            break;
        }
        if (player_plc == goal_plc) {
            std::cout << "\033[2J\033[1;1H"; //it clears the screen
            std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
            std::cout << print_as_color<ansi_color_code::blue>("Congratulations!, You won the hardest game I've ever code ツ. ") << std::endl;
            player_plc = temp;
            break;
        }
    }
}
void Maze::setGraph()
{
    graph.root = new Graph::Node(player_plc->getIndex());
    graph.Nodes.push_back(graph.root);
    graph.N++;
    curNode = graph.root;
    insert(player_plc->getIndex());
    for (auto& i : graph.Nodes) {
        grid[i->value].setNode(i);
    }
    setNodesNotChecked();
}
void Maze::insert(size_t n)
{
    for (auto& j : graph.Nodes)
        if (j->value == n) {
            curNode = j;
            break;
        }
    for (auto& i : grid[n].neighbors) {
        if (i) {
            if (std::binary_search(notInserted.begin(), notInserted.end(), i->getIndex())) {
                graph.Nodes.push_back(new Graph::Node(i->getIndex(), curNode));
                graph.N++;
            }
        }
    }
    //remove n from notInserted
    notInserted.erase(std::remove(notInserted.begin(), notInserted.end(), n), notInserted.end());
    size_t flag {};
    for (auto& j : graph.Nodes) {
        if (j->value == n) {
            curNode = j;
            flag = 1;
        }
    }
    if (!flag)
        return;
    for (auto& i : curNode->children)
        insert(i->value);
}
void Maze::BFS()
{
    size_t i {}, n {};
    while (n < graph.N) {
        for (auto& j : graph.Nodes)
            if (j->get_depth() == i) {
                j->setChecked();
                graph.lastChecked = j;
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                std::cout << "\033[2J\033[1;1H"; //it clears the screen
                std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
                std::cout << print_as_color<ansi_color_code::blue>("BFS:") << std::endl;
                std::cout << print_as_color<ansi_color_code::red>("✔ :Current Path") << std::endl;
                std::cout << print_as_color<ansi_color_code::yellow>("✘ :Checked Paths") << std::endl;
                printMaze();
                if (j == goal_plc->nodeOfCell) {
                    n = graph.N;
                    graph.lastChecked = nullptr;
                    break;
                }
                n++;
            }
        i++;
    }
}
void Maze::preorder(Graph::Node* pn, bool finished)
{
    if (this->finished)
        return;
    pn->setChecked();
    graph.lastChecked = pn;
    if (pn == goal_plc->nodeOfCell)
        this->finished = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cout << "\033[2J\033[1;1H"; //it clears the screen
    std::cout << print_as_color<ansi_color_code::magenta>("███╗░░░███╗░█████╗░███████╗███████╗  ░██████╗░█████╗░██╗░░░░░██╗░░░██╗███████╗██████╗░\n████╗░████║██╔══██╗╚════██║██╔════╝  ██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██╔══██╗\n██╔████╔██║███████║░░███╔═╝█████╗░░  ╚█████╗░██║░░██║██║░░░░░╚██╗░██╔╝█████╗░░██████╔╝\n██║╚██╔╝██║██╔══██║██╔══╝░░██╔══╝░░  ░╚═══██╗██║░░██║██║░░░░░░╚████╔╝░██╔══╝░░██╔══██╗\n██║░╚═╝░██║██║░░██║███████╗███████╗  ██████╔╝╚█████╔╝███████╗░░╚██╔╝░░███████╗██║░░██║\n╚═╝░░░░░╚═╝╚═╝░░╚═╝╚══════╝╚══════╝  ╚═════╝░░╚════╝░╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n") << std::endl;
    std::cout << print_as_color<ansi_color_code::blue>("DFS(preorder):") << std::endl;
    std::cout << print_as_color<ansi_color_code::red>("✔ :Current Path") << std::endl;
    std::cout << print_as_color<ansi_color_code::yellow>("✘ :Checked Paths") << std::endl;
    printMaze();
    if (pn->children.size()) {
        //reverse children for more optimom search
        std::reverse(pn->children.begin(), pn->children.end());
        for (auto& i : pn->children)
            preorder(i, this->finished);
        //back to the first state
        std::reverse(pn->children.begin(), pn->children.end());
    }
}

void Maze::setNodesNotChecked()
{
    for (auto& i : graph.Nodes)
        i->setNotChecked();
    graph.lastChecked = nullptr;
}
void Maze::mainMenu()
{
    std::cout << print_as_color<ansi_color_code::blue>("How to solve?(Enter 1,2,3,4)\n1)BFS\n2)DFS(preorder)\n3)Game mode\n4)Exit.\n");
    char c {};
    while (c != '4' && c != '3' && c != '2' && c != '1') {
        std::cin >> c;
        switch (c) {
        case '1':
            std::cout << print_as_color<ansi_color_code::blue>("Please enter delay between steps(ms):") << std::endl;
            std::cin >> delay;
            BFS();
            setNodesNotChecked();
            break;
        case '2':
            std::cout << print_as_color<ansi_color_code::blue>("Please enter delay between steps(ms):") << std::endl;
            std::cin >> delay;
            preorder(graph.root, false);
            setNodesNotChecked();
            finished = false;
            break;
        case '3':
            gameMode();
            break;
        default:
            break;
        }
    }
}