#pragma once
#include "IntervalTreePrice.hpp"
#include "Filtro.hpp"
#include <vector>

class FiltroPreco : public Filtro
{
private:
    NodePrice *root;
    double maxPrice;

    void collectIndex(double maxPrice, NodePrice *node, HashSet<int> &result);
    HashSet<int> filterUntilMaxPrice(int maxPrice, NodePrice *root);

public:
    FiltroPreco(NodePrice *root, double maxPrice) : maxPrice(maxPrice), root(root) {}
    HashSet<int> aplicar() override
    {
        HashSet<int> result = filterUntilMaxPrice(maxPrice, root);
        return result;
    }
};

void FiltroPreco::collectIndex(double maxPrice, NodePrice *node, HashSet<int> &baseFilmes)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->price > maxPrice)
        return;

    if (node->price <= maxPrice)
    {
        for (int index = 0; index < node->indexList.size(); index++)
        {
            baseFilmes.put(node->indexList[index]);
        }
    }

    if (node->left != nullptr)
        collectIndex(maxPrice, node->left, baseFilmes);

    if (node->right != nullptr)
        collectIndex(maxPrice, node->right, baseFilmes);
}

HashSet<int> FiltroPreco::filterUntilMaxPrice(int maxPrice, NodePrice *root)
{
    HashSet<int> result;

    if (maxPrice < 0)
        return result;

    collectIndex(maxPrice, root, result);
    return result;
}
