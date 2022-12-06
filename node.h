#ifndef NODE_H
#define NODE_H


#include <memory>
#include <vector>
class Node
{

public:
    Node( int newIndex, std::vector<int> newNeighborsIndexes);


    std::string showNode() const;


    const std::vector<int> &getNeighborsIndexes() const;

    int getIndex() const;

    const std::shared_ptr<Node> &getPrev_node() const;
    void setPrev_node(const std::shared_ptr<Node> &newPrev_node);

private:

    std::shared_ptr<Node> prev_node;
//    std::shared_ptr<Node> next_node;
    int index;
    std::vector<int> neighborsIndexes;
};

std::ostream & operator<<(std::ostream & os, const Node & b);
#endif // NODE_H
