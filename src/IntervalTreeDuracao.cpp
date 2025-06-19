#pragma once

#include "../Bibliotecas/ArrayList.hpp"
#include "../Bibliotecas/Filme.hpp"
#include "../Bibliotecas/ExpressionTree.hpp"
#include "../Bibliotecas/IntervalTreeDuration.hpp"
#include <climits>

int greaterValue(int a, int b)
{
    return (a > b) ? a : b;
}
int nodeHeight(Node *node)
{
    return node ? node->height : 0;
}
int balancingFactor(Node *node)
{
    if (!node)
        return 0;
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}
Node *turnLeft(Node **node)
{
    Node *head = (*node);
    Node *leftNode = head->left;
    Node *rightSon = leftNode->right;

    leftNode->right = head;
    head->left = rightSon;

    leftNode->height = greaterValue(nodeHeight(leftNode->right), nodeHeight(leftNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = leftNode;
    return (*node);
}
Node *turnRight(Node **node)
{
    Node *head = (*node);
    Node *rightNode = head->right;
    Node *leftSon = rightNode->left;

    head->right = leftSon;
    rightNode->left = head;

    rightNode->height = greaterValue(nodeHeight(rightNode->right), nodeHeight(rightNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = rightNode;
    return (*node);
}
Node *turnLeftRight(Node **node)
{
    (*node)->left = turnLeft(&(*node)->right);
    return turnRight(node);
}
Node *turnRightLeft(Node **node)
{
    (*node)->right = turnRight(&(*node)->right);
    return turnLeft(node);
}
void balancing(Node **node)
{
    int bl = balancingFactor(*node);

    // Decide qual é a rotação necessária
    if (bl < -1 && balancingFactor((*node)->right) <= 0)
        *node = turnLeft(node);
    else if (bl > 1 && balancingFactor((*node)->left) >= 0)
        *node = turnRight(node);
    else if (bl > 1 && balancingFactor((*node)->left) < 0)
        *node = turnLeftRight(node);
    else if (bl < -1 && balancingFactor((*node)->right) > 0)
        *node = turnRightLeft(node);
}
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
        newNode->height = 1;
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
    // atualiza a altura do nó
    node->height = greaterValue(nodeHeight(node->left), nodeHeight(node->right)) + 1;

    // Chama a função de balanceamento para garantir que a árvore seja uma AVL.
    balancing(&node);

    // atualiza a maior duração da subárvore. Útil para função de filtragem
    int maxLeft = (node->left ? node->left->maxDuration : INT_MIN);
    int maxRight = (node->right ? node->right->maxDuration : INT_MIN);
    int maxCurrent = (node->duration > maxLeft) ? node->duration : maxLeft;
    node->maxDuration = (maxCurrent > maxRight) ? maxCurrent : maxRight;

    return node;
}
