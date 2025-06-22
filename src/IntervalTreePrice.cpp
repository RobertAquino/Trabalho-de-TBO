#pragma once

#include <vector>
#include "../Bibliotecas/Cinema.hpp"
#include "../Bibliotecas/IntervalTreePrice.hpp"
#include <climits>

int greaterValue(int a, int b)
{
    return (a > b) ? a : b;
}
int nodeHeight(NodePrice *node)
{
    return node ? node->height : 0;
}
int balancingFactor(NodePrice *node)
{
    if (!node)
        return 0;
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}
NodePrice *turnLeft(NodePrice **node)
{
    NodePrice *head = (*node);
    NodePrice *leftNode = head->left;
    NodePrice *rightSon = leftNode->right;

    leftNode->right = head;
    head->left = rightSon;

    leftNode->height = greaterValue(nodeHeight(leftNode->right), nodeHeight(leftNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = leftNode;
    return (*node);
}
NodePrice *turnRight(NodePrice **node)
{
    NodePrice *head = (*node);
    NodePrice *rightNode = head->right;
    NodePrice *leftSon = rightNode->left;

    head->right = leftSon;
    rightNode->left = head;

    rightNode->height = greaterValue(nodeHeight(rightNode->right), nodeHeight(rightNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = rightNode;
    return (*node);
}
NodePrice *turnLeftRight(NodePrice **node)
{
    (*node)->left = turnLeft(&(*node)->right);
    return turnRight(node);
}
NodePrice *turnRightLeft(NodePrice **node)
{
    (*node)->right = turnRight(&(*node)->right);
    return turnLeft(node);
}
void balancing(NodePrice **node)
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
bool insertNode(NodePrice **root, std::vector<Cinema> &cinemas, int &index)
{
    // Compara se a duração é valida. Alguns filmes tem duração nula
    if (index >= cinemas.size() || cinemas[index].precoIngresso < 0)
    {
        index++;
        return false;
    }

    *root = insertRec(*root, cinemas, index);
    return true;
}
NodePrice *insertRec(NodePrice *node, std::vector<Cinema> &cinemas, int &index)
{
    // Insere o novo nodo
    if (node == nullptr)
    {
        int price = cinemas[index].precoIngresso;
        NodePrice *newNode = new NodePrice(price);
        newNode->height = 1;
        newNode->indexList.push_back(index);
        index++;
        return newNode;
    }
    // Procura o nodo nulo
    if (cinemas[index].precoIngresso < node->price)
    {
        node->left = insertRec(node->left, cinemas, index);
    }
    else if (cinemas[index].precoIngresso > node->price)
    {
        node->right = insertRec(node->right, cinemas, index);
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
    int maxLeft = (node->left ? node->left->maxPrice : INT_MIN);
    int maxRight = (node->right ? node->right->maxPrice : INT_MIN);
    int maxCurrent = (node->price > maxLeft) ? node->price : maxLeft;
    node->maxPrice = (maxCurrent > maxRight) ? maxCurrent : maxRight;

    return node;
}
