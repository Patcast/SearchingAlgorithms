#include "node.h"
#include <ostream>
#include <sstream>




Node::Node(int newIndex, std::vector<int> newNeighborsIndexes):
    index{newIndex},neighborsIndexes{newNeighborsIndexes}
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
  result << "NodeIndex = " <<index;
  result << "\t||\tNodeNeighbours = ";
  for(auto n: neighborsIndexes)
  result << "  " <<n;
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

void Node::setPrev_node(const std::shared_ptr<Node> &newPrev_node)
{
    prev_node = newPrev_node;
}

