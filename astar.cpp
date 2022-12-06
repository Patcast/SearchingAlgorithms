#include "astar.h"
#include <iostream>

//  TODO:
//  Add a way to visualize path found.
//  Empty collections after use or before using.



std::shared_ptr<Node> AStar::breadthFirstSearch(int start_index, int goal_index)
{
    std::queue<std::shared_ptr<Node>> frontier;
    std::unordered_map<int,std::shared_ptr<Node>> reached;
    std::shared_ptr<Node> current;

    std::shared_ptr<Node> start =gameWord_ptr->makeNode(start_index);


    frontier.push(start);
    reached[start_index] = start;
    start->setPrev_node(nullptr);

    std::cout << "Path finding: Start-> "<<start_index<<", Goal-> " <<goal_index<< std::endl;
    while (!frontier.empty()) {
        current = frontier.front();
        frontier.pop();

        if (current->getIndex() == goal_index) {
              std::cout << "Goal Found"<< std::endl;
              break;
        }

        for (int neighborIndex : current->getNeighborsIndexes()) {

            if (reached.find(neighborIndex) == reached.end()) {
              std::shared_ptr<Node> next = gameWord_ptr->makeNode(neighborIndex);
              next->setPrev_node(current);
              frontier.push(next);
              reached[neighborIndex]=(next);
            }
        }
    }
    return current;
}

void AStar::printPathFound(std::shared_ptr<Node> ptr_goal)
{
    std::shared_ptr<Node> current =  ptr_goal;

    do{

        std::cout << *current << std::endl;
        current =current->getPrev_node();

    }while(current!=nullptr);
}


void AStar::setGameWord_ptr(GameWorld *newGameWord_ptr)
{
    gameWord_ptr = newGameWord_ptr;
}

