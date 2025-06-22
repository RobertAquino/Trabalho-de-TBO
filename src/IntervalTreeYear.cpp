#pragma once

#include "../Bibliotecas/ArrayList.hpp"
#include "../Bibliotecas/Filme.hpp"
#include "../Bibliotecas/IntervalTreeYear.hpp"
#include <climits>

int greaterValue(int a, int b)
{
    return (a > b) ? a : b;
}
int nodeHeight(NodeYear *node)
{
    return node ? node->height : 0;
}
int balancingFactor(NodeYear *node)
{
    if (!node)
        return 0;
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}
NodeYear *turnLeft(NodeYear **node)
{
    NodeYear *head = (*node);
    NodeYear *leftNode = head->left;
    NodeYear *rightSon = leftNode->right;

    leftNode->right = head;
    head->left = rightSon;

    leftNode->height = greaterValue(nodeHeight(leftNode->right), nodeHeight(leftNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = leftNode;
    return (*node);
}
NodeYear *turnRight(NodeYear **node)
{
    NodeYear *head = (*node);
    NodeYear *rightNode = head->right;
    NodeYear *leftSon = rightNode->left;

    head->right = leftSon;
    rightNode->left = head;

    rightNode->height = greaterValue(nodeHeight(rightNode->right), nodeHeight(rightNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = rightNode;
    return (*node);
}
NodeYear *turnLeftRight(NodeYear **node)
{
    (*node)->left = turnLeft(&(*node)->right);
    return turnRight(node);
}
NodeYear *turnRightLeft(NodeYear **node)
{
    (*node)->right = turnRight(&(*node)->right);
    return turnLeft(node);
}
void balancing(NodeYear **node)
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
bool insertNode(NodeYear **root, std::vector<Filme> &filmes, int &index)
{
    // Compara se a duração é valida. Alguns filmes tem duração nula
    if (index >= filmes.size() || filmes[index].startYear < 0)
    {
        index++;
        return false;
    }

    *root = insertRec(*root, filmes, index);
    return true;
}
NodeYear *insertRec(NodeYear *node, std::vector<Filme> &filmes, int &index)
{
    // Insere o novo nodo
    if (node == nullptr)
    {
        int starYear = filmes[index].startYear;
        NodeYear *newNode = new NodeYear(starYear);
        newNode->height = 1;
        newNode->indexList.push_back(index);
        index++;
        return newNode;
    }
    // Procura o nodo nulo
    if (filmes[index].startYear < node->year)
    {
        node->left = insertRec(node->left, filmes, index);
    }
    else if (filmes[index].startYear > node->year)
    {
        node->right = insertRec(node->right, filmes, index);
    }

    // Não cria uma nova lista se a duração já existir, apenas atualiza indexList
    else
    {
        node->indexList.push_back(index);
        index++;
        return node;
    }
    // atualiza a altura do nó
    node->height = greaterValue(nodeHeight(node->left), nodeHeight(node->right)) + 1;

    // Chama a função de balanceamento para garantir que a árvore seja uma AVL.
    balancing(&node);

    // atualiza a maior duração da subárvore. Útil para função de filtragem
    int maxLeft = (node->left ? node->left->maxYear : INT_MIN);
    int maxRight = (node->right ? node->right->maxYear : INT_MIN);
    int maxCurrent = (node->year > maxLeft) ? node->year : maxLeft;
    node->year = (maxCurrent > maxRight) ? maxCurrent : maxRight;

    return node;
}
