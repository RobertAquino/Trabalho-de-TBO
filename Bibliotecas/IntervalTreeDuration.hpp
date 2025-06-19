#pragma once

#include "ArrayList.hpp"
#include "Filme.hpp"
#include "ExpressionTree.hpp"

class Node
{

public:
    int duration;
    int maxDuration;
    int index;
    Node *right;
    Node *left;
    int height;

public:
    Node(int duration, int indice) : duration(duration), maxDuration(duration),
                                     index(index), right(nullptr), left(nullptr), height(0) {}
    ~Node()
    {
        delete left;
        delete right;
    }
};

class IntervalTreeDuration
{
public:
    Node *root;

    IntervalTreeDuration() : root(nullptr) {}
    ~IntervalTreeDuration()
    {
        delete root;
    }

private:
    int greaterValue(int a, int b);
    int nodeHeight(Node *node);
    int balancingFactor(Node *node);
    Node *turnLeft(Node **node);
    Node *turnRight(Node **node);
    Node *turnLeftRight(Node **node);
    Node *turnRightLeft(Node **node);
    void balancing(Node **node);
    bool insertNode(Node *root, ArrayList<Filme> filmes, int *index);
    Node *insertRec(Node *node, ArrayList<Filme> filmes, int *index);
};