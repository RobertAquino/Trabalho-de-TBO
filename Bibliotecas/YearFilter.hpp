#pragma once
#include "IntervalTreeYear.hpp"
#include "Filtro.hpp"
#include <vector>

class FiltroAno : public Filtro
{
private:
    NodeYear *root;
    int maxYear;
    int minYear;

    void collectIndex(int maxYear, int minYear, NodeYear *node, HashSet<int> &result);
    HashSet<int> filterByInterval(int maxYear, int minYear, NodeYear *root);

public:
    FiltroAno(NodeYear *root, int maxYear, int minYear) : root(root), maxYear(maxYear), minYear(minYear) {}

    HashSet<int> aplicar() override
    {
        return filterByInterval(maxYear, minYear, root);
    }
};

void FiltroAno::collectIndex(int maxYear, int minYear, NodeYear *node, HashSet<int> &result)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->year < minYear || node->year > maxYear)
        return;

    if (node->year <= maxYear && node->year >= minYear)
    {
        for (int index = 0; index < node->indexList.size(); index++)
        {
            result.put(node->indexList[index]);
        }
    }

    if (node->left != nullptr && node->maxYear > minYear)
        collectIndex(maxYear, minYear, node->left, result);

    if (node->right != nullptr && node->maxYear < maxYear)
        collectIndex(maxYear, minYear, node->right, result);
}

HashSet<int> FiltroAno::filterByInterval(int maxYear, int minYear, NodeYear *root)
{
    HashSet<int> result;

    if (minYear < 0 || maxYear < minYear)
        return result;

    collectIndex(maxYear, minYear, root, result);
    return result;
}
