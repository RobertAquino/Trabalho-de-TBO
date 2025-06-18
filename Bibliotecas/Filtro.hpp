#pragma once

#include "Cinema.hpp"
#include "ArrayList.hpp"
#include "Filme.hpp"

class Filtro
{
public:
    virtual ArrayList<Filme> aplicar(const ArrayList<Filme> &filmes) const = 0;
    virtual ~Filtro() {}
};
