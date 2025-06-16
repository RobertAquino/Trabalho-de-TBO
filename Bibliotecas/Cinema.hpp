#pragma once

#include "Filme.hpp"
#include "ArrayList.hpp"
#include "Localizacao.hpp"
#include <iostream>

class Cinema
{
public:
    long cinemaId;
    std::string nomeCinema;
    Localizacao localizacao;
    double precoIngresso;
    ArrayList<Filme> filmesEmExibicao;

    Cinema();
    ~Cinema();
};