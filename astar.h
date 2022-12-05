#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"
#include <queue>
#include <unordered_set>
class AStar
{
public:
    void breadthFirstSearch( std::shared_ptr<Node> start);

private:
    // probably use a priority queu for the list
    // OPEN QUEU
    // Close QUEU
    std::queue<std::shared_ptr<Node>> frontier;
    std::unordered_set<std::shared_ptr<Node>> reached;
};

#endif // ASTAR_H
