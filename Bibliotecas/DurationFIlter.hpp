
#include "IntervalTreeDuration.hpp"
#include <vector>

void collectIndex(int maxDuration, int minDuration, NodeDuration *node, std::vector<int> &result)
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
            result.push_back(node->indexList[index]);
        }
    }

    if (node->left != nullptr && node->maxDuration > minDuration)
        collectIndex(maxDuration, minDuration, node->left, result);

    if (node->right != nullptr && node->maxDuration < maxDuration)
        collectIndex(maxDuration, minDuration, node->right, result);
}

std::vector<int> filterByInterval(int maxDuration, int minDuration, NodeDuration *root)
{
    std::vector<int> result;

    if (minDuration < 0 || maxDuration < minDuration)
        return result;

    collectIndex(maxDuration, minDuration, root, result);
}
std::vector<int> filterByDuration(int duration, NodeDuration *root)
{
    std::vector<int> result;
    if (duration < 0)
        return result;

    collectIndex(duration, duration, root, result);
    return result;
}
