#include "astarcontroller.h"
#include <iostream>


AStarController::AStarController()
{

    aStar = std::make_unique <AStar>( GameWorld::Instance()->getTotalRows(), GameWorld::Instance()->getTotalColumns());

}

void AStarController::runDijktra(int start_index, int goal_index)
{
    aStar->printPathFound(aStar->aStarSearch(start_index,goal_index,0.0));
}

void AStarController::runAStar(int start_index, int goal_index,float heuristic)
{

    if(start_index<0||start_index>= GameWorld::Instance()->getTotalColumns()* GameWorld::Instance()->getTotalRows()||goal_index<0||goal_index>= GameWorld::Instance()->getTotalColumns()* GameWorld::Instance()->getTotalRows()){
       std::cout<<"Searching algorithm: INDEX OUT OF BOUNDS"<<std::endl;
    }
//    else  aStar->aStarSearch(start_index,goal_index,heuristic);
    else aStar->printPathFound(aStar->aStarSearch(start_index,goal_index,heuristic));

}
