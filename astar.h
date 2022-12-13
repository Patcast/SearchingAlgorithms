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

    std::shared_ptr<Node> aStarSearch(int start_index, int goal_index);
    void printPathFound(std::shared_ptr<Node> ptr_goal);
    void setGameWord_ptr(GameWorld *newGameWord_ptr);


    void setHeuristicFactor(float newHeuristicFactor);

    float getHeuristicFactor() const;

    void testSpecialFigures();
private:

    std::shared_ptr<Node> makeNode(int index);
    std::vector<int> getNeighboursTileIndex(std::pair<int, int> coordinates);
    void updateNode(int goalIndex, std::shared_ptr<Node> neighborNode, std::shared_ptr<Node>  topNode , std::priority_queue<queuePair, std::vector<queuePair>> &openQueueRef);
    void updateNode(std::shared_ptr<Node> neighborNode, std::shared_ptr<Node>  topNode , std::priority_queue<queuePair, std::vector<queuePair>> &openQueueRef);
    float heuristic(int neighborIndex, int goalIndex);

    GameWorld* gameWord_ptr;
    int totalRows,totalColumns;
    std::unordered_map<int,std::shared_ptr<Node>> nodes;
    const int tileOffSets [MAX_NEIGHBORS][NODE_DIMENSION] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    float heuristicFactor{0.2}; //shortest path can only be found if the heuristic is admisable. i.e. meaning it never overstimates the remaining distance.
};





#endif // ASTAR_H
