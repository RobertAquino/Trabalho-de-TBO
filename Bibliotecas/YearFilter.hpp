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
    // Caso base: se o nó é nulo, não há o que fazer.
    if (node == nullptr)
    {
        return;
    }

    // 1. Verifica se vale a pena ir para a ESQUERDA
    // Só vamos para a esquerda se o valor mínimo do intervalo for menor que a duração do nó atual.
    if (minYear < node->year)
    {
        collectIndex(maxYear, minYear, node->left, result);
    }

    // 2. Coleta os índices do NÓ ATUAL
    // Se a duração do nó atual está dentro do intervalo [min, max].
    if (node->year >= minYear && node->year <= maxYear)
    {
        for (size_t i = 0; i < node->indexList.size(); ++i)
        {
            result.put(node->indexList[i]);
        }
    }

    // 3. Verifica se vale a pena ir para a DIREITA
    // Só vamos para a direita se o valor máximo do intervalo for maior que a duração do nó atual.
    if (maxYear > node->year)
    {
        collectIndex(maxYear, minYear, node->right, result);
    }
}

HashSet<int> FiltroAno::filterByInterval(int maxYear, int minYear, NodeYear *root)
{
    HashSet<int> result;

    if (minYear < 0 || maxYear < minYear)
        return result;

    collectIndex(maxYear, minYear, root, result);
    return result;
}
