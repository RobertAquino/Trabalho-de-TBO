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
    HashSet<int> filterUntilMaxPrice(double maxPrice, NodePrice *root);

public:
    FiltroPreco(NodePrice *root, double maxPrice) : maxPrice(maxPrice), root(root) {}
    HashSet<int> aplicar() override
    {
        HashSet<int> result = filterUntilMaxPrice(maxPrice, root);
        return result;
    }
};

void FiltroPreco::collectIndex(double maxPrice, NodePrice *node, HashSet<int> &result)
{
    // Retorna se o nodo for nulo
    if (node == nullptr)
    {
        return;
    }

    // A função é chamada recursivamente a esquerda para receber todos os valores menores do que o intervalo
    collectIndex(maxPrice, node->left, result);

    // Se o preço do nó for maior do que o limite de preço a função retorna
    if (node->price > maxPrice)
    {
        return;
    }

    // Adiciona na lista de resultados todos os cinemas que estão dentro do intervalo de preço
    for (size_t i = 0; i < node->indexList.size(); ++i)
    {
        result.put(node->indexList[i]);
    }

    // A função é chamada recursivamente para receber todos os valores a direita do nó raiz, ainda dentro
    // intervalo de preço
    collectIndex(maxPrice, node->right, result);
}
HashSet<int> FiltroPreco::filterUntilMaxPrice(double maxPrice, NodePrice *root)
{
    HashSet<int> result;

    if (maxPrice < 0)
        return result;

    // Esta função chama uma função auxiliar para percorrer todos os nodos na árvore que estão dentro
    // do intervalo, e coloca o índice de todos os cinemas dentro da lista result
    collectIndex(maxPrice, root, result);
    return result;
}
