#ifndef ASTAR_H
#define ASTAR_H

#include "gameworld.h"
#include "node.h"
#include <queue>
#include <unordered_set>

class AStar
{
public:
    AStar(int totalRows, int totalColumns);

    std::shared_ptr<Node> breadthFirstSearch(int start_index, int goal_index);
    std::shared_ptr<Node> dijkstraSearch(int start_index, int goal_index);
    void printPathFound(std::shared_ptr<Node> ptr_goal);
    void setGameWord_ptr(GameWorld *newGameWord_ptr);
    void testQueue();

private:

    int totalRows,totalColumns;
    std::shared_ptr<Node> makeNode(int index);
    std::vector<int> getNeighbourTileIndex(int row, int col);
    GameWorld* gameWord_ptr;
    std::unordered_map<int,std::shared_ptr<Node>> nodes;
    const int tileOffSets [MAX_NEIGHBORS][NODE_DIMENSION] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

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
typedef std::pair<float, int> queuePair;

struct CompNodePtByCostSoFar {
  bool operator()(
    std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
  {
    return n1->getCostSoFar() < n2->getCostSoFar();
  }
};




#endif // ASTAR_H
