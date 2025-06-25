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

    void collectIndex(int maxDuration, int minDuration, NodeDuration *node, HashSet<int> &result);
    HashSet<int> filterByInterval(int maxDuration, int minDuration, NodeDuration *root);

public:
    FiltroDuration(NodeDuration *root, int maxDuration, int minDuration) : root(root), maxDuration(maxDuration), minDuration(minDuration) {}

    HashSet<int> aplicar() override
    {
        HashSet<int> result = filterByInterval(maxDuration, minDuration, root);
        return result;
    }
};

void FiltroDuration::collectIndex(int max, int min, NodeDuration *node, HashSet<int> &result)
{
    // Caso base: se o nó é nulo, não há o que fazer.
    if (node == nullptr)
    {
        return;
    }

    // 1. Verifica se vale a pena ir para a ESQUERDA
    // Só vamos para a esquerda se o valor mínimo do intervalo for menor que a duração do nó atual.
    if (min < node->duration)
    {
        collectIndex(max, min, node->left, result);
    }

    // 2. Coleta os índices do NÓ ATUAL
    // Se a duração do nó atual está dentro do intervalo [min, max].
    if (node->duration >= min && node->duration <= max)
    {
        for (size_t i = 0; i < node->indexList.size(); ++i)
        {
            result.put(node->indexList[i]);
        }
    }

    // 3. Verifica se vale a pena ir para a DIREITA
    // Só vamos para a direita se o valor máximo do intervalo for maior que a duração do nó atual.
    if (max > node->duration)
    {
        collectIndex(max, min, node->right, result);
    }
}

HashSet<int> FiltroDuration::filterByInterval(int maxDuration, int minDuration, NodeDuration *root)
{
    HashSet<int> result;

    if (minDuration < 0 || maxDuration < minDuration)
        return result;

    collectIndex(maxDuration, minDuration, root, result);
    return result;
}
