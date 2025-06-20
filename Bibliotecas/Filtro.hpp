#pragma once

#include "Cinema.hpp"
#include "ArrayList.hpp"
#include "HashSet.hpp"
#include "Filme.hpp"

class Filtro
{
public:
    virtual HashSet<int> aplicar() = 0;
    virtual ~Filtro() {}
};
