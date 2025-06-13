#pragma once

#include <vector>
#include <iostream>
#include "../Bibliotecas/GenresFilter.hpp"

void getGenresFilter(const ArrayList<Filme> &filmes, ArrayList<genresFilter> &genresFilter, Genres genres,
     ArrayList<int> &lista, bool primeiro)
{
    std::vector<int> j;
    for (int i = 0; i < filmes.getSize(); i++)
    {
        //corrigir o uso do operando(ArrayList)
        if(filmes[i].genres != genres)
        {
            genresFilter[i].isHere = false;
        }
        else
        {
            genresFilter[i].isHere = true;
            j.push_back(i);
        }
    }
     for(int i = 0; i < genresFilter.getSize(); i++)
    {
        if (genresFilter.isHere)
            lista[i] =
    }
}
