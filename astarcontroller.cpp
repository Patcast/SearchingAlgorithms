#include "astarcontroller.h"


AStarController::AStarController()
{

    gameWord_ptr= GameWorld::Instance();
    gameWord_ptr->loadWorld(":/images/worldmap.png",20,60,100.0);
    aStar.setGameWord_ptr(gameWord_ptr);
    aStar.breadthFirstSearch(5);

}


