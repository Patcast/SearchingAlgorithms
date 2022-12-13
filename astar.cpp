#include "astar.h"
#include <iostream>
#include <iomanip>

//  TODO:
//  Add a way to visualize path found.
//  Empty collections after use or before using.



AStar::AStar(int totalRows, int totalColumns) : totalRows(totalRows),
    totalColumns(totalColumns)
{

}

void AStar::testSpecialFigures(){
    int numEnemies=0;
    int numHealthPacks = 0;
    for(unsigned long i=0;i<gameWord_ptr->specialFigures.size();i++){
        if(gameWord_ptr->specialFigures[i].has_value()){ //Check if there is a value in that index.
            if(Enemy* enemyReference =dynamic_cast<Enemy*>(gameWord_ptr->specialFigures[i]->get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
                numEnemies++;
               std::cout<<"I am an enemy defeatedStatus = "<<enemyReference->getDefeated()<<std::endl;
            }
            else {
                numHealthPacks++;
            }
        }
    }
    std::cout<<"Number of Enemies: "<<numEnemies<<std::endl;
    std::cout<<"Number of HealthPacks: "<<numHealthPacks<<std::endl;
}


std::shared_ptr<Node> AStar::aStarSearch(int start_index, int goalIndex)
{

    std::priority_queue<queuePair, std::vector<queuePair>> openQueue;
    int topIndex;

    nodes.clear();
    nodes.emplace(start_index, std::make_shared<Node>(start_index,gameWord_ptr->getTiles()[start_index]->getValue(),getNeighboursTileIndex(gameWord_ptr->getCoordinatesFromIndex(start_index))));
    nodes[start_index]->setCostSoFarToZero();
    openQueue.push(std::make_pair(0,start_index));
    std::cout << "aStar search: Start-> "<<start_index<<", Goal-> " <<goalIndex<< std::endl;

    while (!openQueue.empty()) {

        topIndex = openQueue.top().second;
        openQueue.pop();

        if (topIndex == goalIndex) {
              std::cout << "Goal Found"<< std::endl;
              break;
        }
        if( !nodes[topIndex]->getCompleted()){ // implies that a node with an index in the queue, must exists in nodes[].

            for (int neighborIndex : nodes[topIndex]->getNeighborsIndexes()) {

                    if (nodes.find(neighborIndex) == nodes.end()) {
                        nodes.emplace(neighborIndex, std::make_shared<Node>(neighborIndex,gameWord_ptr->getTiles()[neighborIndex]->getValue(),getNeighboursTileIndex(gameWord_ptr->getCoordinatesFromIndex(neighborIndex))));
                        updateNode(goalIndex,nodes[neighborIndex],nodes[topIndex],openQueue);
                    }

//                    else if((!nodes[neighborIndex]->getCompleted()&& nodes[topIndex]-> getCostSoFar() +nodes[neighborIndex]->getIncomingCost() < nodes[neighborIndex]->getCostSoFar()))
                    else if((nodes[topIndex]-> getCostSoFar() +nodes[neighborIndex]->getIncomingCost() < nodes[neighborIndex]->getCostSoFar()))
                    {
                        updateNode(goalIndex,nodes[neighborIndex],nodes[topIndex],openQueue);
                    }
            }
            nodes[topIndex]->setCompleted(true);
        }
    }
    return nodes[topIndex];
}


float AStar::heuristic(int neighborIndex, int goalIndex){

    std::pair<int, int> neighborCoordinates = gameWord_ptr->getCoordinatesFromIndex(neighborIndex);
    std::pair<int, int> goalCoordinates = gameWord_ptr->getCoordinatesFromIndex(goalIndex);
    return heuristicFactor*std::abs(neighborCoordinates.first-goalCoordinates.first+neighborCoordinates.second-goalCoordinates.second );
}

float AStar::getHeuristicFactor() const
{
    return heuristicFactor;
}

void AStar::setHeuristicFactor(float newHeuristicFactor)
{
    heuristicFactor = newHeuristicFactor;
}



void AStar::printPathFound(std::shared_ptr<Node> ptr_goal)
{
    std::shared_ptr<Node> current =  ptr_goal;
    std::cout<<"Tiles opened:"<<nodes.size()<<std::endl;

    do{

        std::cout << *current << std::endl;
        current =current->getPrev_node();

    }while(current!=nullptr);
}


void AStar::setGameWord_ptr(GameWorld *newGameWord_ptr)
{
    gameWord_ptr = newGameWord_ptr;
}





std::vector<int> AStar::getNeighboursTileIndex( std::pair<int, int> coordinates)
{
    std::vector<int> n;
    for(int i =0;i<MAX_NEIGHBORS;i++){
        int nRow = coordinates.first+tileOffSets[i][0];
        int nCol = coordinates.second+tileOffSets[i][1];
        if(
                (nRow<totalRows)&&
                (nCol<totalColumns)&&
                (nRow>=0)&&
                (nCol>=0)
                ){
            n.push_back(gameWord_ptr->getIndexFromCoordinates(nRow,nCol));        }
    }
    return n;
}

void AStar::updateNode(int goalIndex,std::shared_ptr<Node> neighborNode, std::shared_ptr<Node> topNode, std::priority_queue<queuePair, std::vector<queuePair> > &openQueueRef)
{
    // aStar Implementation
    neighborNode->setCostSoFar(topNode->getCostSoFar());
    neighborNode->setPrev_node(topNode);
    openQueueRef.push(std::make_pair((-1)*(neighborNode->getCostSoFar()+heuristic(neighborNode->getIndex(),goalIndex)),neighborNode->getIndex()));
}






