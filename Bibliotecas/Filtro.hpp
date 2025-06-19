#pragma once

#include "Cinema.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "Filme.hpp"

class Filtro
{
public:
    virtual HashMap<std::string, int> aplicar(const ArrayList<Filme> &filmes) const = 0;
    virtual ~Filtro() {}
};
