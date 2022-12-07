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

    void setCostViaParent(float newCostViaParent);

    float getCostViaParent() const;
    float getIncomingCost() const;

private:

    std::shared_ptr<Node> prev_node;
    int index;
    std::vector<int> neighborsIndexes;
    float costViaParent;
    float incomingCost;
};

std::ostream & operator<<(std::ostream & os, const Node & b);
#endif // NODE_H
