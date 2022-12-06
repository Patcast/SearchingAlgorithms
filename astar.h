#ifndef ASTAR_H
#define ASTAR_H

#include "gameworld.h"
#include "node.h"
#include <queue>
#include <unordered_set>
class AStar
{
public:
    void breadthFirstSearch(int start_index);

    void setGameWord_ptr(GameWorld *newGameWord_ptr);

private:
    // probably use a priority queu for the list
    // OPEN QUEU
    // Close QUEU
    std::queue<std::shared_ptr<Node>> frontier;
    std::unordered_set<std::shared_ptr<Node>> reached;
    GameWorld* gameWord_ptr;
};

#endif // ASTAR_H
