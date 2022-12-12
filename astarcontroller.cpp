#include "astarcontroller.h"


AStarController::AStarController()
{
    gameWord_ptr= GameWorld::Instance(":/images/worldmap.png",20,60,100.0);
    aStar = std::make_unique <AStar>(gameWord_ptr->getTotalRows(),gameWord_ptr->getTotalColumns());
    aStar->setGameWord_ptr(gameWord_ptr);
//    gameWord_ptr->getTiles()[3]->setValue(200.0);
//    gameWord_ptr->getTiles()[33]->setValue(200.0);
//    gameWord_ptr->getTiles()[63]->setValue(200.0);
//    gameWord_ptr->getTiles()[93]->setValue(200.0);
//    gameWord_ptr->getTiles()[123]->setValue(200.0);
}

void AStarController::runDijktra(int start_index, int goal_index)
{
    aStar->printPathFound(aStar->dijkstraSearch(start_index,goal_index));
}


