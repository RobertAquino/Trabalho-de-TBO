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

public:
    Node(int duration, int indice) : duration(duration), maxDuration(duration),
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

    IntervalTreeDuration() : root(nullptr) {}
    ~IntervalTreeDuration()
    {
        delete root;
    }

private:
    bool insertNode(Node *root, ArrayList<Filme> filmes, int *index);
    Node *insertRec(Node *node, ArrayList<Filme> filmes, int *index);
};