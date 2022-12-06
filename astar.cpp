#include "astar.h"
#include <iostream>



void AStar::breadthFirstSearch(int start_index)
{
    std::unordered_set<int> existingNodesIndexes;
    std::shared_ptr<Node> start =gameWord_ptr->makeNode(start_index);
    frontier.push(start);
    reached.insert(start); // posible nodes that can be reached starting from start(Node)
    existingNodesIndexes.insert(start->getIndex()); // keeps track of created nodes

    while (!frontier.empty()) {
        std::shared_ptr<Node> current = frontier.front();
        frontier.pop();

        std::cout << "  Visiting " << *current << '\n';
        for (int neighborIndex : current->getNeighborsIndexes()) {
            if (existingNodesIndexes.find(neighborIndex) == existingNodesIndexes.end()) {
              std::shared_ptr<Node> next = gameWord_ptr->makeNode(neighborIndex);
              existingNodesIndexes.insert(next->getIndex());
              frontier.push(next);
              reached.insert(next);
            }
        }
    }
}


void AStar::setGameWord_ptr(GameWorld *newGameWord_ptr)
{
    gameWord_ptr = newGameWord_ptr;
}

