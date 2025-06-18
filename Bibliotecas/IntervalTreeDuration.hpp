#pragma once

#include "ArrayList.hpp"
#include "Filme.hpp"
#include "ExpressionTree.hpp"

class Node
{

public:
    int duration;
    int maxFim;
    int index;
    Node *right;
    Node *left;

public:
    Node(int duration, int indice) : duration(duration), maxFim(end),
                                     index(index), right(nullptr), left(nullptr) {}

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

    IntervalTreeDuration() : root(nullptr)
    {
    }
    ~IntervalTreeDuration()
    {
        delete root;
    }

private:
    void insertNode();

    void insertRec();
};