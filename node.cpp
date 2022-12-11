#include "node.h"
#include <ostream>
#include <sstream>




Node::Node(int newIndex,float newIncomingCost, std::vector<int> newNeighborsIndexes):
    index{newIndex},neighborsIndexes{newNeighborsIndexes},incomingCost{newIncomingCost}
{

}


std::ostream &operator<<(std::ostream &os, const Node &n)
{
  os << n.showNode() << std::endl;
  return os;
}

std::string Node::showNode() const
{
  std::stringstream result;
  result << "Node: indx:" <<index;
  result << "\t inCost:" <<incomingCost;
  result << "\tneighbours:{";
  for(auto n: neighborsIndexes) result << " " <<n;
  result << "}";
  return result.str();

}

const std::vector<int> &Node::getNeighborsIndexes() const
{
    return neighborsIndexes;
}

int Node::getIndex() const
{
    return index;
}

const std::shared_ptr<Node> &Node::getPrev_node() const
{
    return prev_node;
}
float Node::getCostViaParent() const
{
    return costViaParent;
}

float Node::getIncomingCost() const
{
    return incomingCost;
}


void Node::setPrev_node(const std::shared_ptr<Node> &newPrev_node)
{
    prev_node = newPrev_node;
}

void Node::setCostViaParent(float newCostViaParent)
{
    costViaParent = newCostViaParent;
}


