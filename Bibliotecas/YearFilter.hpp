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
    // Retorna se o nodo é nulo
    if (node == nullptr)
    {
        return;
    }
    // Verifica se o nodo é maior do que o intervalo mínimo, se for, a função chama recursivamente para
    //  a esquerda até chegar no limite inferior do intervalo
    if (minYear < node->year)
    {
        collectIndex(maxYear, minYear, node->left, result);
    }

    // Verifica se o nodo atual está dentro do limite minímo e máximo e adiciona todos os indices de indexList
    // no HashSet result
    if (node->year >= minYear && node->year <= maxYear)
    {
        for (size_t i = 0; i < node->indexList.size(); ++i)
        {
            result.put(node->indexList[i]);
        }
    }

    // Verifica se o nodo atual é menor do que o limite superir, se for, a função chama recursivamente a
    // a direito buscando todos os nodos até chegar no limite superior
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

    // A função collectIndex é chamada como função auxiliar para percorrer todos os nodos contidos dentro dos
    // intervalos máximos e mínimos
    collectIndex(maxYear, minYear, root, result);
    return result;
}
