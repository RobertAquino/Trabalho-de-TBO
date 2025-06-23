
#include "IntervalTreePrice.hpp"
#include <vector>

void collectIndex(int maxPrice, NodePrice *node, std::vector<int> &result)
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
            result.push_back(node->indexList[index]);
        }
    }

    if (node->left != nullptr)
        collectIndex(maxPrice, node->left, result);

    if (node->right != nullptr)
        collectIndex(maxPrice, node->right, result);
}

std::vector<int> filterUntilMaxPrice(int maxPrice, NodePrice *root)
{
    std::vector<int> result;

    if (maxPrice < 0)
        return result;

    collectIndex(maxPrice, root, result);
    return result;
}
