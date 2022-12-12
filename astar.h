#ifndef ASTAR_H
#define ASTAR_H

#include "gameworld.h"
#include "node.h"
#include <queue>
#include <unordered_set>

typedef std::pair<float, int> queuePair;

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


    std::shared_ptr<Node> makeNode(int index);
    std::vector<int> getNeighbourTileIndex(int row, int col);
    void updateNode(std::shared_ptr<Node> neighborNode,std::shared_ptr<Node>  topNode ,std::priority_queue<queuePair, std::vector<queuePair>> &openQueueRef);
    GameWorld* gameWord_ptr;
    int totalRows,totalColumns;
    std::unordered_map<int,std::shared_ptr<Node>> nodes;
    const int tileOffSets [MAX_NEIGHBORS][NODE_DIMENSION] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

};





#endif // ASTAR_H
