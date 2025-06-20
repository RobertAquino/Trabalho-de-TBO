#pragma once

#include "ArrayList.hpp"
#include "Filme.hpp"

class NodeYear
{

public:
    int year;
    int maxDuration;
    ArrayList<int> indexList;
    NodeYear *right;
    NodeYear *left;
    int height;

public:
    NodeYear(int duration) : year(year), maxDuration(duration),
                             right(nullptr), left(nullptr), height(0) {}
    ~NodeYear()
    {
        delete left;
        delete right;
    }
};

class IntervalTreeDuration
{
public:
    NodeYear *root;

    IntervalTreeDuration() : root(nullptr) {}
    ~IntervalTreeDuration()
    {
        delete root;
    }

private:
    int greaterValue(int a, int b);
    int nodeHeight(NodeYear *node);
    int balancingFactor(NodeYear *node);
    NodeYear *turnLeft(NodeYear **node);
    NodeYear *turnRight(NodeYear **node);
    NodeYear *turnLeftRight(NodeYear **node);
    NodeYear *turnRightLeft(NodeYear **node);
    void balancing(NodeYear **node);
    bool insertNode(NodeYear *root, ArrayList<Filme> filmes, int &index);
    NodeYear *insertRec(NodeYear *node, ArrayList<Filme> filmes, int &index);
};
