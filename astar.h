#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"
#include <queue>
#include <unordered_set>
class AStar
{
public:
    void breadthFirstSearch( Node start);

private:
    // probably use a priority queu for the list
    // OPEN QUEU
    // Close QUEU
    std::queue<Node> frontier;
    std::unordered_set<Node> reached;
};

#endif // ASTAR_H
