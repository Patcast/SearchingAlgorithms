#ifndef ASTAR_H
#define ASTAR_H

#include "gameworld.h"
#include "node.h"
#include <queue>
#include <unordered_set>

class AStar
{
public:
    std::shared_ptr<Node> breadthFirstSearch(int start_index, int goal_index);
    void printPathFound(std::shared_ptr<Node> ptr_goal);
    void setGameWord_ptr(GameWorld *newGameWord_ptr);

private:
    // probably use a priority queu for the list
    // OPEN QUEU
    // Close QUEU

    GameWorld* gameWord_ptr;
};

//struct NodePtrEqualByIndex {
//public:
//    bool operator()(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2) const {
//        return (n1->getIndex() == n2->getIndex())?true:false;
//    }
//};

//struct NodePtrHashByIndex {
//public:
//    size_t operator()(std::shared_ptr<Node> n1) const {
//        int index = n1->getIndex();
//        return std::hash<int>()(index);
//    }
//};




#endif // ASTAR_H
