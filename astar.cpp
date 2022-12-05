#include "astar.h"
#include <iostream>



void AStar::breadthFirstSearch(std::shared_ptr<Node> start)
{
    frontier.push(start);
    reached.insert(start); // posible nodes that can be reached starting from start(Node)

    while (!frontier.empty()) {
        std::shared_ptr<Node> current = frontier.front();
        frontier.pop();

//        std::cout << "  Visiting " << current << '\n';
//      for (char next : graph.neighbors(current)) {
//        if (reached.find(next) == reached.end()) {
//          frontier.push(next);
//          reached.insert(next);
//        }
//      }
//    }
  }
}

