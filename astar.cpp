#include "astar.h"
#include <iostream>
#include <iomanip>

//  TODO:
//  Add a way to visualize path found.
//  Empty collections after use or before using.
//  Handle exemption if makeNode() returns NULL.




std::shared_ptr<Node> AStar::dijkstraSearch(int start_index, int goal_index)
{

    std::priority_queue<queuePair, std::vector<queuePair>> openQueue;
    int topIndex;

    nodes.clear();
    nodes.emplace(start_index, std::make_shared<Node>(start_index,gameWord_ptr->getTiles()[start_index]->getValue(),getNeighbourTileIndex(gameWord_ptr->getTiles()[start_index]->getYPos(),gameWord_ptr->getTiles()[start_index]->getXPos())));
    nodes[start_index]->setCostSoFarToZero();
    openQueue.push(std::make_pair(0,start_index));
    std::cout << "Dijkstra search: Start-> "<<start_index<<", Goal-> " <<goal_index<< std::endl;

    while (!openQueue.empty()) {

        topIndex = openQueue.top().second;
        openQueue.pop();

        if (topIndex == goal_index) {
              std::cout << "Goal Found"<< std::endl;
              break;
        }
        if( !nodes[topIndex]->getCompleted()){ // implies that a node with an index in the queue, must exists in nodes[].

            for (int neighborIndex : nodes[topIndex]->getNeighborsIndexes()) {

                    if (nodes.find(neighborIndex) == nodes.end()) {
                        nodes.emplace(neighborIndex, std::make_shared<Node>(neighborIndex,gameWord_ptr->getTiles()[neighborIndex]->getValue(),getNeighbourTileIndex(gameWord_ptr->getTiles()[neighborIndex]->getYPos(),gameWord_ptr->getTiles()[neighborIndex]->getXPos())));
                        updateNode(nodes[neighborIndex],nodes[topIndex],openQueue);
                    }

                    else if((!nodes[neighborIndex]->getCompleted()&& nodes[topIndex]-> getCostSoFar() +nodes[neighborIndex]->getIncomingCost() < nodes[neighborIndex]->getCostSoFar()))
                    {
                        updateNode(nodes[neighborIndex],nodes[topIndex],openQueue);
                    }
            }
            nodes[topIndex]->setCompleted(true);
        }
    }
    return nodes[topIndex];
}



void AStar::printPathFound(std::shared_ptr<Node> ptr_goal)
{
    std::shared_ptr<Node> current =  ptr_goal;
     std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\nCost of path: " <<current ->getCostSoFar() << std::endl;

    do{

        std::cout << *current << std::endl;
        current =current->getPrev_node();

    }while(current!=nullptr);
}


void AStar::setGameWord_ptr(GameWorld *newGameWord_ptr)
{
    gameWord_ptr = newGameWord_ptr;
}


std::shared_ptr<Node> AStar::makeNode(int index)
{
    //Check if tile exists
    try {


        std::shared_ptr<Node> node = std::make_shared<Node>(index,gameWord_ptr->getTiles()[index]->getValue(),getNeighbourTileIndex(gameWord_ptr->getTiles()[index]->getYPos(),gameWord_ptr->getTiles()[index]->getXPos()));
        return node;
    } catch (const std::exception& e) {
        std::cout << e.what(); // information from error printed
        return NULL;
    }
}


std::vector<int> AStar::getNeighbourTileIndex(int row,int col)
{
    std::vector<int> n;
//    std::cout<<" -----("<<row<<","<<col<<")-----"<<std::endl;
    for(int i =0;i<MAX_NEIGHBORS;i++){
        int nRow = row+tileOffSets[i][0];
        int nCol = col+tileOffSets[i][1];

        if(
                (nRow<totalRows)&&
                (nCol<totalColumns)&&
                (nRow>=0)&&
                (nCol>=0)
                ){
            n.push_back(gameWord_ptr->getIndexFromCoordinates(nRow,nCol));
//            std::cout<<" ("<<nRow<<","<<nCol<<")"<<std::endl;
        }
    }
    return n;
}

void AStar::updateNode(std::shared_ptr<Node> neighborNode, std::shared_ptr<Node> topNode, std::priority_queue<queuePair, std::vector<queuePair> > &openQueueRef)
{
    // Is the call by reference correct for the queue
    neighborNode->setCostSoFar(topNode->getCostSoFar());
    neighborNode->setPrev_node(topNode);
    openQueueRef.push(std::make_pair((-1)*(neighborNode->getCostSoFar()),neighborNode->getIndex()));
}




AStar::AStar(int totalRows, int totalColumns) : totalRows(totalRows),
    totalColumns(totalColumns)
{}
