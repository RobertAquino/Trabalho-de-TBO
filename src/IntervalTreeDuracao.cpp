#pragma once

#include "../Bibliotecas/ArrayList.hpp"
#include "../Bibliotecas/Filme.hpp"
#include "../Bibliotecas/ExpressionTree.hpp"
#include "../Bibliotecas/IntervalTreeDuration.hpp"

bool insertNode(Node *root, ArrayList<Filme> filmes, int *index)
{
    if (filmes[index].runTimeMinutes < 0 || filmes[index].runTimeMinutes == nullptr)
        index++;
    return false;

    insertRec(root, filmes, index);
}
void insertRec(Node *node, ArrayList<Filme> filmes, int *index)
{
    if (node == nullptr)
    {
        Node *newNode = new Node(filmes[index].runTimeMinutes, index++);
    }
    if (filmes[index].runTimeMinutes > node->duration)
        return insertRec(node->right, filmes, index);

    return insertRec(node->left, filmes, index);

    if ()
}
