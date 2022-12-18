#ifndef ASTAR_H
#define ASTAR_H


#include "node.h"
#include <queue>
#include <unordered_set>

typedef std::pair<float, int> queuePair;

class AStar
{
public:
    AStar(int totalRows, int totalColumns);
    int aStarSearch(int start_index, int goal_index);
    void printPathFound(int goalIndex);
    void setHeuristicFactor(float newHeuristicFactor);
    float getHeuristicFactor() const;
    void testSpecialFigures();
private:

    std::shared_ptr<Node> makeNode(int index);
    std::vector<int> getNeighboursTileIndex(std::pair<int, int> coordinates);
    inline void updateNode(int goalIndex,int neighborIndex, int topIndex, std::priority_queue<queuePair, std::vector<queuePair> > &openQueueRef);
    inline float heuristic(int neighborIndex, int goalIndex);

    int totalRows,totalColumns;
    float heuristicFactor {0.2}; //shortest path can only be found if the heuristic is admisable. i.e. meaning it never overstimates the remaining distance.
};





#endif // ASTAR_H
