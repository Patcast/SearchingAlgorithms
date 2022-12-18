#include "astar.h"
#include <iostream>
#include <iomanip>
#include "gameworld.h"



AStar::AStar(int totalRows, int totalColumns) : totalRows(totalRows),
    totalColumns(totalColumns)
{

}


int AStar::aStarSearch(int start_index, int goalIndex)
{

    std::priority_queue<queuePair, std::vector<queuePair>> openQueue;
    int topIndex;


    std::for_each( GameWorld::Instance()->getNodes().begin(),  GameWorld::Instance()->getNodes().end(), [](const std::unique_ptr<Node>& node_ptr) {
        node_ptr->resetNodeForSearch();
    });
     GameWorld::Instance()->getNodes()[start_index]->setCostSoFarToZero();

    openQueue.push(std::make_pair(0,start_index));
    std::cout << "aStar search: Start-> "<<start_index<<", Goal-> " <<goalIndex<< std::endl;

    while (!openQueue.empty()) {

        topIndex = openQueue.top().second;
        openQueue.pop();

        if (topIndex == goalIndex) {
              std::cout << "Goal Found"<< std::endl;
              break;
        }
        if( ! GameWorld::Instance()->getNodes()[topIndex]->getCompleted()){ // implies that a node with an index in the queue, must exists in nodes[].
            for (int neighborIndex :  GameWorld::Instance()->getNodes()[topIndex]->getNeighborsIndexes()) {
                if(( GameWorld::Instance()->getNodes()[topIndex]-> getCostSoFar() + GameWorld::Instance()->getNodes()[neighborIndex]->getIncomingCost() <=  GameWorld::Instance()->getNodes()[neighborIndex]->getCostSoFar()))
                {
                    updateNode(goalIndex,neighborIndex,topIndex,openQueue);
                }
            }
             GameWorld::Instance()->getNodes()[topIndex]->setCompleted(true);
        }
    }
    return topIndex;
}


inline float AStar::heuristic(int neighborIndex, int goalIndex){

    std::pair<int, int> neighborCoordinates =  GameWorld::Instance()->getCoordinatesFromIndex(neighborIndex);
    std::pair<int, int> goalCoordinates =  GameWorld::Instance()->getCoordinatesFromIndex(goalIndex);
    float heuristic =heuristicFactor*(std::abs(neighborCoordinates.first-goalCoordinates.first)+std::abs(neighborCoordinates.second-goalCoordinates.second));
    return heuristic;
}

float AStar::getHeuristicFactor() const
{

    return heuristicFactor;
}

std::vector<int> AStar::getShortestPath(int start_index, int goal_index)
{
    std::vector<int> searchOutput;
    int nextNode = aStarSearch(start_index,goal_index);
    do{

        searchOutput.push_back(GameWorld::Instance()->getNodes()[nextNode]->getIndex());
        nextNode = GameWorld::Instance()->getNodes()[nextNode]->getPrevNodeIndex();
    }while(nextNode!=-1);
    return searchOutput;
}

void AStar::setHeuristicFactor(float newHeuristicFactor)
{
    heuristicFactor = newHeuristicFactor;
    std::cout<<heuristicFactor<<std::endl;
}



void AStar::printPathFound(int goalIndex)
{

    int nextNode = goalIndex;
    do{

        std::cout << * GameWorld::Instance()->getNodes()[nextNode] << std::endl;
        nextNode = GameWorld::Instance()->getNodes()[nextNode]->getPrevNodeIndex();

    }while(nextNode!=-1);
}


inline void AStar::updateNode(int goalIndex,int neighborIndex, int topIndex, std::priority_queue<queuePair, std::vector<queuePair> > &openQueueRef)
{
     GameWorld::Instance()->getNodes()[neighborIndex]->setCostSoFar( GameWorld::Instance()->getNodes()[topIndex]->getCostSoFar());

     GameWorld::Instance()->getNodes()[neighborIndex]->setPrevNodeIndex(topIndex);
     openQueueRef.push(std::make_pair((-1)*( GameWorld::Instance()->getNodes()[neighborIndex]->getCostSoFar()+heuristic( GameWorld::Instance()->getNodes()[neighborIndex]->getIndex(),goalIndex)),GameWorld::Instance()->getNodes()[neighborIndex]->getIndex()));
}






