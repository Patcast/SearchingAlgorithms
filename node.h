#ifndef NODE_H
#define NODE_H


#include "world.h"
#include <memory>
#include <vector>
#include <QObject>

#define MAX_NEIGHBORS 4
#define NODE_DIMENSION 2
class Node : public QObject
{

public:
    Node(int newIndex, float incomingCost, int totalRows, int totalColumns);


    std::string showNode() const;


    const std::vector<int> &getNeighborsIndexes() const;

    int getIndex() const;

    void setCostSoFar(float costSoFarOfParent);
    void setCostSoFarToZero();
    float getCostSoFar() const;
    float getIncomingCost() const;
    bool getCompleted() const;
    void setCompleted(bool newCompleted);
    void resetNodeForSearch();
    const std::shared_ptr<Tile> &getSpecialFigure_ptr() const;
    void setSpecialFigure_ptr(const std::shared_ptr<Tile> &newSpecialFigure_ptr);

    int getPrevNodeIndex() const;
    void setPrevNodeIndex(int newPrevNodeIndex);

signals:
    void iluminateNode();

private:

    inline std::vector<int> getNeighboursTileIndex();
    int getIndexFromCoordinates(const int row_index, const int col_index){return totalColumns*row_index +col_index;};
    std::pair<int, int> getCoordinates(){return (std::make_pair<int,int>( index/totalColumns,index%totalColumns));};
    int prevNodeIndex {-1};
    int index;
    const int tileOffSets [MAX_NEIGHBORS][NODE_DIMENSION] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    std::vector<int> neighborsIndexes;
    float costSoFar;
    float incomingCost;
    bool completed {false};
    std::shared_ptr<Tile> specialFigure_ptr {nullptr};
    int totalRows, totalColumns;
};

std::ostream & operator<<(std::ostream & os, const Node & b);
#endif // NODE_H
