#include "astar.h"
#include <iostream>
#include <iomanip>

//  TODO:
//  Add a way to visualize path found.



AStar::AStar(int totalRows, int totalColumns) : totalRows(totalRows),
    totalColumns(totalColumns)
{

}




int AStar::aStarSearch(int start_index, int goalIndex, float heuristic)
{

    std::priority_queue<queuePair, std::vector<queuePair>> openQueue;
    int topIndex;
    setHeuristicFactor(heuristic);

    std::for_each(gameWord_ptr->getNodes().begin(), gameWord_ptr->getNodes().end(), [](const std::unique_ptr<Node>& node_ptr) {
        node_ptr->resetNodeForSearch();
    });
    gameWord_ptr->getNodes()[start_index]->setCostSoFarToZero();

    openQueue.push(std::make_pair(0,start_index));
    std::cout << "aStar search: Start-> "<<start_index<<", Goal-> " <<goalIndex<< std::endl;

    while (!openQueue.empty()) {

        topIndex = openQueue.top().second;
        openQueue.pop();

        if (topIndex == goalIndex) {
              std::cout << "Goal Found"<< std::endl;
              break;
        }
        if( !gameWord_ptr->getNodes()[topIndex]->getCompleted()){ // implies that a node with an index in the queue, must exists in nodes[].
            for (int neighborIndex : gameWord_ptr->getNodes()[topIndex]->getNeighborsIndexes()) {

                if((gameWord_ptr->getNodes()[topIndex]-> getCostSoFar() +gameWord_ptr->getNodes()[neighborIndex]->getIncomingCost() <= gameWord_ptr->getNodes()[neighborIndex]->getCostSoFar()))
                {
                    updateNode(goalIndex,neighborIndex,topIndex,openQueue);
                }
            }
            gameWord_ptr->getNodes()[topIndex]->setCompleted(true);
        }
    }
    return topIndex;
}


float AStar::heuristic(int neighborIndex, int goalIndex){

    std::pair<int, int> neighborCoordinates = gameWord_ptr->getCoordinatesFromIndex(neighborIndex);
    std::pair<int, int> goalCoordinates = gameWord_ptr->getCoordinatesFromIndex(goalIndex);
    float heuristic =heuristicFactor*(std::abs(neighborCoordinates.first-goalCoordinates.first)+std::abs(neighborCoordinates.second-goalCoordinates.second));
    return heuristic;
}

float AStar::getHeuristicFactor() const
{
    return heuristicFactor;
}

void AStar::setHeuristicFactor(float newHeuristicFactor)
{
    heuristicFactor = newHeuristicFactor;
}



void AStar::printPathFound(int goalIndex)
{

    int nextNode = goalIndex;
    do{

        std::cout << *gameWord_ptr->getNodes()[nextNode] << std::endl;
        nextNode =gameWord_ptr->getNodes()[nextNode]->getPrevNodeIndex();

    }while(nextNode!=-1);
}


void AStar::setGameWord_ptr(GameWorld *newGameWord_ptr)
{
    gameWord_ptr = newGameWord_ptr;
}







inline void AStar::updateNode(int goalIndex,int neighborIndex, int topIndex, std::priority_queue<queuePair, std::vector<queuePair> > &openQueueRef)
{
    gameWord_ptr->getNodes()[neighborIndex]->setCostSoFar(gameWord_ptr->getNodes()[topIndex]->getCostSoFar());

    gameWord_ptr->getNodes()[neighborIndex]->setPrevNodeIndex(topIndex);
    openQueueRef.push(std::make_pair((-1)*(gameWord_ptr->getNodes()[neighborIndex]->getCostSoFar()+heuristic(gameWord_ptr->getNodes()[neighborIndex]->getIndex(),goalIndex)),gameWord_ptr->getNodes()[neighborIndex]->getIndex()));
}






