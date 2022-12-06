#include "astar.h"
#include <iostream>

//TODO: Add a way to visualize path found.

std::shared_ptr<Node> AStar::breadthFirstSearch(int start_index, int goal_index)
{
    std::unordered_set<int> existingNodesIndexes;
    std::shared_ptr<Node> start =gameWord_ptr->makeNode(start_index);
    std::shared_ptr<Node> current;

    frontier.push(start);
    reached.insert(start); // posible nodes that can be reached starting from start(Node)
    existingNodesIndexes.insert(start->getIndex()); // keeps track of created nodes
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
            if (existingNodesIndexes.find(neighborIndex) == existingNodesIndexes.end()) {
              std::shared_ptr<Node> next = gameWord_ptr->makeNode(neighborIndex);

              existingNodesIndexes.insert(next->getIndex());
              next->setPrev_node(current);
              frontier.push(next);
              reached.insert(next);
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

