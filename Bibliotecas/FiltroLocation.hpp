#pragma once

#include "Filtro.hpp"
#include "KDTree.hpp"
#include "HashSet.hpp"

class FiltroLocation : public Filtro
{
private:
    KDTree *arvore;
    int x, y, r;

public:
    FiltroLocation(KDTree *arvore, int x, int y, int r)
        : arvore(arvore), x(x), y(y), r(r) {}

    HashSet<int> aplicar() override
    {
        return arvore->findInRadius(x, y, r);
    }
};
