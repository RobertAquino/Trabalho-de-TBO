#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>

#include "HashSet.hpp"
#include "Cinema.hpp"

class KDTree
{
public:
    struct KDNode
    {
        int index;
        KDNode *left = nullptr;
        KDNode *right = nullptr;
        bool vertical;

        KDNode(int idx, bool vert) : index(idx), vertical(vert) {}
    };

    KDTree(std::vector<Cinema> &points, const std::vector<Cinema> &listaBaseCinema)
        : listaBaseCinema(listaBaseCinema)
    {
        indices.resize(points.size());
        for (int i = 0; i < (int)points.size(); ++i)
        {
            indices[i] = i;
        }

        root = build(indices, 0, (int)indices.size(), true, points);
    }

    ~KDTree()
    {
        freeTree(root);
    }

    HashSet<int> findInRadius(int x, int y, int r) const
    {
        HashSet<int> result;
        radiusSearch(root, x, y, r, result);
        return result;
    }

private:
    KDNode *root;
    const std::vector<Cinema> &listaBaseCinema;
    std::vector<int> indices;

    int partition(std::vector<int> &idxs, int left, int right, bool vertical, const std::vector<Cinema> &points)
    {
        int pivotIdx = idxs[right];
        const auto &pivot = points[pivotIdx];
        int i = left;

        for (int j = left; j < right; ++j)
        {
            const auto &a = points[idxs[j]];
            bool cond = vertical ? (a.localizacao.x < pivot.localizacao.x)
                                 : (a.localizacao.y < pivot.localizacao.y);
            if (cond)
            {
                std::swap(idxs[i], idxs[j]);
                ++i;
            }
        }
        std::swap(idxs[i], idxs[right]);
        return i;
    }

    void quickSelect(std::vector<int> &idxs, int left, int right, int k, bool vertical, const std::vector<Cinema> &points)
    {
        if (left >= right)
            return;

        int pivotIndex = partition(idxs, left, right, vertical, points);

        if (k == pivotIndex)
            return;
        else if (k < pivotIndex)
            quickSelect(idxs, left, pivotIndex - 1, k, vertical, points);
        else
            quickSelect(idxs, pivotIndex + 1, right, k, vertical, points);
    }

    KDNode *build(std::vector<int> &idxs, int start, int end, bool vertical, const std::vector<Cinema> &points)
    {
        if (start >= end)
        {
            return nullptr;
        }

        int mid = (start + end) / 2;
        quickSelect(idxs, start, end - 1, mid, vertical, points);

        KDNode *node = new KDNode(idxs[mid], vertical);
        node->left = build(idxs, start, mid, !vertical, points);
        node->right = build(idxs, mid + 1, end, !vertical, points);
        return node;
    }

    void freeTree(KDNode *node)
    {
        if (!node)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

    void radiusSearch(KDNode *node, double x, double y, double r, HashSet<int> &result) const
    {
        if (!node)
            return;

        const Cinema &c = listaBaseCinema[node->index];
        double dx = c.localizacao.x - x;
        double dy = c.localizacao.y - y;
        double dist2 = dx * dx + dy * dy;
        double r2 = r * r;

        if (dist2 <= r2)
        {
            result.put(node->index); // índice original
        }

        double delta = node->vertical ? dx : dy;

        if (delta > -r)
            radiusSearch(node->left, x, y, r, result);
        if (delta < r)
            radiusSearch(node->right, x, y, r, result);
    }
};
