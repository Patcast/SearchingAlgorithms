#include "node.h"
#include <ostream>
#include <sstream>




Node::Node(int newIndex, float newIncomingCost,int totalRows, int totalColumns):
    index{newIndex},incomingCost{newIncomingCost}
{
   neighborsIndexes= getNeighboursTileIndex( newIndex, totalRows,totalColumns);
}

inline std::vector<int> Node::getNeighboursTileIndex( int index,int totalRows, int totalColumns)
{
    std::vector<int> n;
    for(int i =0;i<MAX_NEIGHBORS;i++){
        int nRow = getCoordinatesFromIndex(index,totalColumns).first+tileOffSets[i][0];
        int nCol = getCoordinatesFromIndex(index,totalColumns).second+tileOffSets[i][1];
        if((nRow<totalRows)&&(nCol<totalColumns)&&(nRow>=0)&&(nCol>=0))n.push_back(getIndexFromCoordinates(nRow,nCol,totalColumns));
    }
    return n;
}

const std::shared_ptr<Tile> &Node::getSpecialFigure_ptr() const
{
    return specialFigure_ptr;
}

void Node::setSpecialFigure_ptr(const std::shared_ptr<Tile> &newSpecialFigure_ptr)
{
    specialFigure_ptr = newSpecialFigure_ptr;
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


