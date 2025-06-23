#pragma once

#include "Cinema.hpp"
#include <vector>
class NodePrice
{

public:
    float price;
    float maxPrice;
    std::vector<int> indexList;
    NodePrice *right;
    NodePrice *left;
    int height;

public:
    NodePrice(float price) : price(price), maxPrice(price),
                             right(nullptr), left(nullptr), height(0) {}
    ~NodePrice()
    {
        delete left;
        delete right;
    }
};

class IntervalTreeDuration
{
public:
    NodePrice *root;

    IntervalTreeDuration() : root(nullptr) {}
    ~IntervalTreeDuration()
    {
        delete root;
    }

private:
    int greaterValue(int a, int b);
    int nodeHeight(NodePrice *node);
    int balancingFactor(NodePrice *node);
    NodePrice *turnLeft(NodePrice **node);
    NodePrice *turnRight(NodePrice **node);
    NodePrice *turnLeftRight(NodePrice **node);
    NodePrice *turnRightLeft(NodePrice **node);
    void balancing(NodePrice **node);
    bool insertNode(NodePrice *root, std::vector<Cinema> filmes, int &index);
    NodePrice *insertRec(NodePrice *node, std::vector<Cinema> filmes, int &index);
};
