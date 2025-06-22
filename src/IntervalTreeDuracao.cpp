#pragma once

#include <vector>
#include "../Bibliotecas/Filme.hpp"
#include "../Bibliotecas/IntervalTreeDuration.hpp"
#include <climits>

int greaterValue(int a, int b)
{
    return (a > b) ? a : b;
}
int nodeHeight(NodeDuration *node)
{
    return node ? node->height : 0;
}
int balancingFactor(NodeDuration *node)
{
    if (!node)
        return 0;
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}
NodeDuration *turnLeft(NodeDuration **node)
{
    NodeDuration *head = (*node);
    NodeDuration *leftNode = head->left;
    NodeDuration *rightSon = leftNode->right;

    leftNode->right = head;
    head->left = rightSon;

    leftNode->height = greaterValue(nodeHeight(leftNode->right), nodeHeight(leftNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = leftNode;
    return (*node);
}
NodeDuration *turnRight(NodeDuration **node)
{
    NodeDuration *head = (*node);
    NodeDuration *rightNode = head->right;
    NodeDuration *leftSon = rightNode->left;

    head->right = leftSon;
    rightNode->left = head;

    rightNode->height = greaterValue(nodeHeight(rightNode->right), nodeHeight(rightNode->left)) + 1;
    head->height = greaterValue(nodeHeight(head->right), nodeHeight(head->left)) + 1;

    (*node) = rightNode;
    return (*node);
}
NodeDuration *turnLeftRight(NodeDuration **node)
{
    (*node)->left = turnLeft(&(*node)->right);
    return turnRight(node);
}
NodeDuration *turnRightLeft(NodeDuration **node)
{
    (*node)->right = turnRight(&(*node)->right);
    return turnLeft(node);
}
void balancing(NodeDuration **node)
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
bool insertNode(NodeDuration **root, std::vector<Filme> &filmes, int &index)
{
    // Compara se a duração é valida. Alguns filmes tem duração nula
    if (index >= filmes.size() || filmes[index].runTimesMinutes < 0)
    {
        index++;
        return false;
    }

    *root = insertRec(*root, filmes, index);
    return true;
}
NodeDuration *insertRec(NodeDuration *node, std::vector<Filme> &filmes, int &index)
{
    // Insere o novo nodo
    if (node == nullptr)
    {
        int duration = filmes[index].runTimesMinutes;
        NodeDuration *newNode = new NodeDuration(duration);
        newNode->height = 1;
        newNode->indexList.push_back(index);
        index++;
        return newNode;
    }
    // Procura o nodo nulo
    if (filmes[index].runTimesMinutes < node->duration)
    {
        node->left = insertRec(node->left, filmes, index);
    }
    else if (filmes[index].runTimesMinutes > node->duration)
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
    int maxLeft = (node->left ? node->left->maxDuration : INT_MIN);
    int maxRight = (node->right ? node->right->maxDuration : INT_MIN);
    int maxCurrent = (node->duration > maxLeft) ? node->duration : maxLeft;
    node->maxDuration = (maxCurrent > maxRight) ? maxCurrent : maxRight;

    return node;
}
