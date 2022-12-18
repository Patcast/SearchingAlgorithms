#ifndef ASTARCONTROLLER_H
#define ASTARCONTROLLER_H

#include "astar.h"



class AStarController
{
public:
    AStarController();
    void runDijktra(int start_index, int goal_index);
    void runAStar(int start_index, int goal_index);


    void setHeuristic(float newHeuristic);

private:
    float heuristic={0};
    std::unique_ptr<AStar> aStar;

};

#endif // ASTARCONTROLLER_H
