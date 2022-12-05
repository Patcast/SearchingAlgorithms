#include "node.h"
#include <ostream>
#include <sstream>




Node::Node(int newIndex, std::vector<int> newNeighborsIndexes):
    index{newIndex},neighborsIndexes{newNeighborsIndexes}
{

}

int Node::getDistance() const
{
    return distance;
}

void Node::setDistance(int newDistance)
{
    distance = newDistance;
}

void Node::setCost(int newCost)
{
    cost = newCost;
}



int Node::getCost() const
{
    return cost;
}

std::ostream &operator<<(std::ostream &os, const Node &n)
{
  os << n.showNode() << std::endl;
  return os;
}

std::string Node::showNode() const
{
  std::stringstream result;
  result << "NodeIndex = " <<index;
  result << "\t||\tNodeNeighbours = ";
  for(auto n: neighborsIndexes)
  result << "  " <<n;
  return result.str();
}
