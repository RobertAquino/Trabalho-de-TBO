#pragma once

#include "filme.hpp"
#include "arrayList.hpp"
#include "localizacao.hpp"
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