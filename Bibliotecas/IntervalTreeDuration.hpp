#pragma once

#include "ArrayList.hpp"
#include "Filme.hpp"
#include "ExpressionTree.hpp"
#include <vector>
class NodeDuration
{

public:
    int duration;
    int maxDuration;
    ArrayList<int> indexList;
    NodeDuration *right;
    NodeDuration *left;
    int height;

public:
    NodeDuration(int duration) : duration(duration), maxDuration(duration),
                                 right(nullptr), left(nullptr), height(0) {}
    ~NodeDuration()
    {
        delete left;
        delete right;
    }
};

class IntervalTreeDuration
{
public:
    NodeDuration *root;

    IntervalTreeDuration() : root(nullptr) {}
    ~IntervalTreeDuration()
    {
        delete root;
    }

private:
    int greaterValue(int a, int b);
    int nodeHeight(NodeDuration *node);
    int balancingFactor(NodeDuration *node);
    NodeDuration *turnLeft(NodeDuration **node);
    NodeDuration *turnRight(NodeDuration **node);
    NodeDuration *turnLeftRight(NodeDuration **node);
    NodeDuration *turnRightLeft(NodeDuration **node);
    void balancing(NodeDuration **node);
    bool insertNode(NodeDuration *root, ArrayList<Filme> filmes, int &index);
    NodeDuration *insertRec(NodeDuration *node, ArrayList<Filme> filmes, int &index);
};
