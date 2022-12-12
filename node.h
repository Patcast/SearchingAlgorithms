#ifndef NODE_H
#define NODE_H


#include <memory>
#include <vector>
class Node
{

public:
    Node( int newIndex,float incomingCost, std::vector<int> newNeighborsIndexes);


    std::string showNode() const;


    const std::vector<int> &getNeighborsIndexes() const;

    int getIndex() const;

    const std::shared_ptr<Node> &getPrev_node() const;
    void setPrev_node(const std::shared_ptr<Node> &newPrev_node);

    void setCostSoFar(float costSoFarOfParent);
    void setCostSoFarToZero();

    float getCostSoFar() const;
    float getIncomingCost() const;

    bool getCompleted() const;
    void setCompleted(bool newCompleted);

private:

    std::shared_ptr<Node> prevNode{nullptr};
    int index;
    std::vector<int> neighborsIndexes;
    float costSoFar;
    float incomingCost;
    bool completed {false};
};

std::ostream & operator<<(std::ostream & os, const Node & b);
#endif // NODE_H
