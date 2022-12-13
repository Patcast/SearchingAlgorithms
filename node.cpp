#include "node.h"
#include <ostream>
#include <sstream>




Node::Node(int newIndex, float newIncomingCost, std::vector<int> newNeighborsIndexes):
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
  result << "Node: indx:" <<index << "\t inCost: " <<incomingCost<<"\t costSoFar: " <<costSoFar << "\t neighbours:{";
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
    return prevNode;
}
float Node::getCostSoFar() const
{
    return costSoFar;
}

float Node::getIncomingCost() const
{
    return incomingCost;
}

bool Node::getCompleted() const
{
    return completed;
}

void Node::setCompleted(bool newCompleted)
{
    completed = newCompleted;
}


void Node::setPrev_node(const std::shared_ptr<Node> &newPrev_node)
{
    prevNode = newPrev_node;
}

void Node::setCostSoFar(float costSoFarOfParent)
{
    costSoFar = costSoFarOfParent+incomingCost;
}

void Node::setCostSoFarToZero()
{
    costSoFar=0.0;
}


