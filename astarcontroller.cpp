#include "astarcontroller.h"
#include <iostream>


AStarController::AStarController()
{
    gameWord_ptr= GameWorld::Instance(":/images/worldmap.png",20,30,100.0);
    aStar = std::make_unique <AStar>(gameWord_ptr->getTotalRows(),gameWord_ptr->getTotalColumns());
    aStar->setGameWord_ptr(gameWord_ptr);
    //gameWord_ptr->testing();
}

void AStarController::runDijktra(int start_index, int goal_index)
{

    aStar->printPathFound(aStar->aStarSearch(start_index,goal_index,0.0));

}

void AStarController::runAStar(int start_index, int goal_index,float heuristic)
{
    aStar->printPathFound(aStar->aStarSearch(start_index,goal_index,heuristic));
}