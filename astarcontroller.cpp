#include "astarcontroller.h"


AStarController::AStarController()
{

    gameWord_ptr= GameWorld::Instance();
    gameWord_ptr->loadWorld(":/images/worldmap.png",20,60,100.0);
    aStar.setGameWord_ptr(gameWord_ptr);

}

void AStarController::executeBreadthFirstSearch(int start_index, int goal_index)
{
    aStar.printPathFound(aStar.breadthFirstSearch(start_index,goal_index));
}


