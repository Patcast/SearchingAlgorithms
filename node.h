#ifndef NODE_H
#define NODE_H


#include <memory>
#include <vector>
class Node
{

public:
    Node( int newIndex, std::vector<int> newNeighborsIndexes);

//    int getDistance() const;
//    void setDistance(int newDistance);
//    int getCost() const;
//    void setCost(int newCost);
//    int getCombinedCost(){return distance+cost;};
    std::string showNode() const;


    const std::vector<int> &getNeighborsIndexes() const;

    int getIndex() const;

private:
//    int distance;
//    int cost;
//    std::shared_ptr<Node> prev_node;
//    std::shared_ptr<Node> next_node;
    int index;
    std::vector<int> neighborsIndexes;
};

std::ostream & operator<<(std::ostream & os, const Node & b);
#endif // NODE_H
