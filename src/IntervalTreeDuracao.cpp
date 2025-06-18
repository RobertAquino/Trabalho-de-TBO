#pragma once

#include "../Bibliotecas/ArrayList.hpp"
#include "../Bibliotecas/Filme.hpp"
#include "../Bibliotecas/ExpressionTree.hpp"
#include "../Bibliotecas/IntervalTreeDuration.hpp"
#include <climits>

bool insertNode(Node **root, ArrayList<Filme> filmes, int *index)
{
    // Compara se a duração é valida. Alguns filmes tem duração nula
    if (filmes[(*index)].runTimesMinutes < 0)
    {
        (*index)++;
        return false;
    }

    *root = insertRec(*root, filmes, index);
    return true;
}
Node *insertRec(Node *node, ArrayList<Filme> filmes, int *index)
{
    // Insere o novo nodo
    if (node == nullptr)
    {
        int duration = filmes[(*index)].runTimesMinutes;
        Node *newNode = new Node(duration, *index);
        (*index)++;
        return newNode;
    }
    // Procura o nodo nulo
    if (filmes[(*index)].runTimesMinutes < node->duration)
    {
        node->left = insertRec(node->left, filmes, index);
    }
    else if (filmes[(*index)].runTimesMinutes > node->duration)
    {
        node->right = insertRec(node->right, filmes, index);
    }
    // Não adiciona a duração se esta já estiver presente na árvore
    else
    {
        (*index)++;
        return node;
    }
    // atualiza a maior duração da subárvore. Útil para função de filtragem
    int maxLeft = (node->left ? node->left->maxDuration : INT_MIN);
    int maxRight = (node->right ? node->right->maxDuration : INT_MIN);
    int maxCurrent = (node->duration > maxLeft) ? node->duration : maxLeft;
    node->maxDuration = (maxCurrent > maxRight) ? maxCurrent : maxRight;

    return node;
}
