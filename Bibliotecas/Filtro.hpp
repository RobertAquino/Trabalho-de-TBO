#pragma once

#include "Cinema.hpp"
#include "ArrayList.hpp"
#include "Filme.hpp"

class Filtro
{
public:
    ArrayList<Filme> filmes;
    ArrayList<Cinema> cinemas;
};
