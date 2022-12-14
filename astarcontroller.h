#ifndef ASTARCONTROLLER_H
#define ASTARCONTROLLER_H

#include "astar.h"
#include "gameworld.h"


//TODO:
// MAKE GAMECONTROLLER A SINGLETON or initialize it in the constructor. Think about if you want to load different maps.

class AStarController
{
public:
    AStarController();
    void runDijktra(int start_index, int goal_index);
    void runAStar(int start_index, int goal_index);


private:
    GameWorld* gameWord_ptr;
    std::unique_ptr<AStar> aStar;

};

#endif // ASTARCONTROLLER_H
