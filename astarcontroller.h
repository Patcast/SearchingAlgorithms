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
private:
    GameWorld* g_ptr;
    AStar aStar;
};

#endif // ASTARCONTROLLER_H
