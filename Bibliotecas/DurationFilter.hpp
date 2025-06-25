#pragma once
#include "IntervalTreeDuration.hpp"
#include "Filtro.hpp"
#include <vector>

class FiltroDuration : public Filtro
{
private:
    NodeDuration *root;
    int maxDuration;
    int minDuration;

    void collectIndex(int maxDuration, int minDuration, NodeDuration *node, HashSet<int> result);
    HashSet<int> filterByInterval(int maxDuration, int minDuration, NodeDuration *root);

public:
    FiltroDuration(NodeDuration *root, int maxYear, int minYear) : root(root), maxDuration(maxDuration), minDuration(minDuration) {}

    HashSet<int> aplicar() override
    {
        HashSet<int> result = filterByInterval(maxDuration, minDuration, root);
        return result;
    }
};
void FiltroDuration::collectIndex(int maxDuration, int minDuration, NodeDuration *node, HashSet<int> result)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->duration < minDuration || node->duration > maxDuration)
        return;

    if (node->duration <= maxDuration && node->duration >= minDuration)
    {
        for (int index = 0; index < node->indexList.size(); index++)
        {
            result.put(node->indexList[index]);
        }
    }

    if (node->left != nullptr && node->maxDuration > minDuration)
        collectIndex(maxDuration, minDuration, node->left, result);

    if (node->right != nullptr && node->maxDuration < maxDuration)
        collectIndex(maxDuration, minDuration, node->right, result);
}

HashSet<int> FiltroDuration::filterByInterval(int maxDuration, int minDuration, NodeDuration *root)
{
    HashSet<int> result;

    if (minDuration < 0 || maxDuration < minDuration)
        return result;

    collectIndex(maxDuration, minDuration, root, result);
    return result;
}
