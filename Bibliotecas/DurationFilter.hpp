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

// função responsável por juntar todas as listas dentro de um intervalo, criando apenas uma lista
void FiltroDuration::collectIndex(int max, int min, NodeDuration *node, HashSet<int> &result)
{
    // retorna quando o nodo for nulo
    if (node == nullptr)
    {
        return;
    }

    // Se o nodo for maior do que o intervalo mínimo, a função chama recursivamente para o nodo a esquerda,
    // com intuito de obter todos os nós até o intervalo mínimo
    if (min < node->duration)
    {
        collectIndex(max, min, node->left, result);
    }

    // Se o nodo estiver entre o limite de duração, todos os valores deste nó são copiados para
    // a lista de resultados
    if (node->duration >= min && node->duration <= max)
    {
        for (size_t i = 0; i < node->indexList.size(); ++i)
        {
            result.put(node->indexList[i]);
        }
    }

    // Se o nodo for menor do que o intervalo máximo de duração, a função chama recursivamente para o nodo da esquerdam
    // com o intuito de obter todos os nós até o intervalo máximo
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

    // Esta função chama uma função auxiliar para percorrer todos os nodos da lista dentro de um intervalo para obter
    // todos os filmes dentro dessa duração
    collectIndex(maxDuration, minDuration, root, result);
    return result;
}
