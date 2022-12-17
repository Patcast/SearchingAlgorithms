#include "astarcontroller.h"
#include <iostream>


AStarController::AStarController()
{
    gameWord_ptr= GameWorld::Instance(":/images/maze3.png",10,0,100.0);
    aStar = std::make_unique <AStar>(gameWord_ptr->getTotalRows(),gameWord_ptr->getTotalColumns());
    aStar->setGameWord_ptr(gameWord_ptr);
    gameWord_ptr->testing();
}

void AStarController::runDijktra(int start_index, int goal_index)
{
    aStar->printPathFound(aStar->aStarSearch(start_index,goal_index,0.0));
}

void AStarController::runAStar(int start_index, int goal_index,float heuristic)
{

    if(start_index<0||start_index>=gameWord_ptr->getTotalColumns()*gameWord_ptr->getTotalRows()||goal_index<0||goal_index>=gameWord_ptr->getTotalColumns()*gameWord_ptr->getTotalRows()){
       std::cout<<"Searching algorithm: INDEX OUT OF BOUNDS"<<std::endl;
    }
//    else  aStar->aStarSearch(start_index,goal_index,heuristic);
    else aStar->printPathFound(aStar->aStarSearch(start_index,goal_index,heuristic));

}
