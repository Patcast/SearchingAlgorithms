#include "node.h"
#include <ostream>
#include <sstream>




Node::Node(int newIndex, float newIncomingCost,int totalRows, int totalColumns):
    index{newIndex},incomingCost{newIncomingCost},totalRows{totalRows},totalColumns{totalColumns}
{
   neighborsIndexes= getNeighboursTileIndex();
}

inline std::vector<int> Node::getNeighboursTileIndex()
{
    std::vector<int> n;
    for(int i =0;i<MAX_NEIGHBORS;i++){
        int nRow = getCoordinates().first+tileOffSets[i][0];
        int nCol = getCoordinates().second+tileOffSets[i][1];
        if((nRow<totalRows)&&(nCol<totalColumns)&&(nRow>=0)&&(nCol>=0))n.push_back(getIndexFromCoordinates(nRow,nCol));
    }
    return n;
}

int Node::getPrevNodeIndex() const
{
    return prevNodeIndex;
}

void Node::setPrevNodeIndex(int newPrevNodeIndex)
{
    prevNodeIndex = newPrevNodeIndex;
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

void Node::resetNodeForSearch()
{
    setCostSoFar(std::numeric_limits<double>::infinity());
    setPrevNodeIndex(-1);
    setCompleted(false);
}




void Node::setCostSoFar(float costSoFarOfParent)
{
    if(specialFigure_ptr==nullptr) costSoFar = costSoFarOfParent+incomingCost;
    else costSoFar = costSoFarOfParent+incomingCost+10;
}

void Node::setCostSoFarToZero()
{
    costSoFar=0.0;
}


