
#include "IntervalTreeYear.hpp"
#include <vector>

void collectIndex(int maxYear, int minYear, NodeYear *node, std::vector<int> &result)
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
            result.push_back(node->indexList[index]);
        }
    }

    if (node->left != nullptr && node->maxYear > minYear)
        collectIndex(maxYear, minYear, node->left, result);

    if (node->right != nullptr && node->maxYear < maxYear)
        collectIndex(maxYear, minYear, node->right, result);
}

std::vector<int> filterByInterval(int maxYear, int minYear, NodeYear *root)
{
    std::vector<int> result;

    if (minYear < 0 || maxYear < minYear)
        return result;

    collectIndex(maxYear, minYear, root, result);
}
std::vector<int> filterByYear(int year, NodeYear *root)
{
    std::vector<int> result;
    if (year < 0)
        return result;

    collectIndex(year, year, root, result);
    return result;
}
