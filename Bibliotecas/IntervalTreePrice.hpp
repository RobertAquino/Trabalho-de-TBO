#pragma once

#include "Cinema.hpp"
#include <vector>
#include <cfloat>

class NodePrice
{

public:
    double price;
    double maxPrice;
    std::vector<double> indexList;
    NodePrice *right;
    NodePrice *left;
    double height;

public:
    NodePrice(double price) : price(price), maxPrice(price),
                              right(nullptr), left(nullptr), height(0) {}
    ~NodePrice()
    {
        delete left;
        delete right;
    }
};

class IntervalTreePrice
{
public:
    NodePrice *root;

    IntervalTreePrice() : root(nullptr) {}
    ~IntervalTreePrice()
    {
        delete root;
    }

    int greaterValue(int a, int b);
    int nodeHeight(NodePrice *node);
    int balancingFactor(NodePrice *node);
    NodePrice *turnLeft(NodePrice **node);
    NodePrice *turnRight(NodePrice **node);
    NodePrice *turnLeftRight(NodePrice **node);
    NodePrice *turnRightLeft(NodePrice **node);
    void balancing(NodePrice **node);
    bool insertNode(NodePrice **root, std::vector<Cinema> &filmes, int index);
    NodePrice *insertRec(NodePrice *node, std::vector<Cinema> &filmes, int index);
};

int IntervalTreePrice::greaterValue(int a, int b)
{
    return (a > b) ? a : b;
}
int IntervalTreePrice::nodeHeight(NodePrice *node)
{
    return node ? node->height : 0;
}
int IntervalTreePrice::balancingFactor(NodePrice *node)
{
    if (!node)
        return 0;
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}
NodePrice *IntervalTreePrice::turnLeft(NodePrice **node)
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
NodePrice *IntervalTreePrice::turnRight(NodePrice **node)
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

NodePrice *IntervalTreePrice::turnLeftRight(NodePrice **node)
{
    (*node)->left = turnRight(&(*node)->left);
    return turnLeft(node);
}
NodePrice *IntervalTreePrice::turnRightLeft(NodePrice **node)
{
    (*node)->right = turnLeft(&(*node)->right);
    return turnRight(node);
}
void IntervalTreePrice::balancing(NodePrice **node)
{
    int bl = balancingFactor(*node);

    // Decide qual é a rotação necessária
    if (bl < -1 && balancingFactor((*node)->right) <= 0)
        *node = turnRight(node);
    else if (bl > 1 && balancingFactor((*node)->left) >= 0)
        *node = turnLeft(node);
    else if (bl > 1 && balancingFactor((*node)->left) < 0)
        *node = turnLeftRight(node);
    else if (bl < -1 && balancingFactor((*node)->right) > 0)
        *node = turnRightLeft(node);
}
bool IntervalTreePrice::insertNode(NodePrice **root, std::vector<Cinema> &cinemas, int index)
{
    // Compara se o indice e o preço é valido.
    if (index >= cinemas.size() || cinemas[index].precoIngresso < 0)
    {
        return false;
    }

    *root = insertRec(*root, cinemas, index);
    return true;
}
NodePrice *IntervalTreePrice::insertRec(NodePrice *node, std::vector<Cinema> &cinemas, int index)
{
    // Insere o novo nodo
    if (node == nullptr)
    {
        double price = cinemas[index].precoIngresso;
        NodePrice *newNode = new NodePrice(price);
        newNode->height = 1;
        newNode->indexList.push_back(index);
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

    // Não cria uma novo nó se este a árvore conter este preço, apenas atualiza a indexList
    else
    {
        node->indexList.push_back(index);
        return node;
    }
    // atualiza a altura do nó
    node->height = greaterValue(nodeHeight(node->left), nodeHeight(node->right)) + 1;

    // Chama a função de balanceamento para garantir que a árvore seja uma AVL.
    balancing(&node);

    // atualiza a maior duração da subárvore. Útil para função de filtragem
    double maxLeft = (node->left ? node->left->maxPrice : DBL_MIN);
    double maxRight = (node->right ? node->right->maxPrice : DBL_MIN);
    double maxCurrent = (node->price > maxLeft) ? node->price : maxLeft;
    node->maxPrice = (maxCurrent > maxRight) ? maxCurrent : maxRight;

    return node;
}
