#include "cell.h"
#include "ansi.h"
Cell::Cell(size_t x, size_t y, size_t ind)
    : x { x }
    , y { y }
    , ind { ind }
    , visited { false }
{
}
// update paths array to indicate which direction was taken
void Cell::updatePaths(Cell* next)
{
    if (next->y < y) { // moved up
        neighbors[U] = next;
        next->neighbors[D] = this;
    } else if (next->y > y) { // moved down
        neighbors[D] = next;
        next->neighbors[U] = this;
    } else if (next->x < x) { // moved left
        neighbors[L] = next;
        next->neighbors[R] = this;
    } else if (next->x > x) { // moved right
        neighbors[R] = next;
        next->neighbors[L] = this;
    }
}