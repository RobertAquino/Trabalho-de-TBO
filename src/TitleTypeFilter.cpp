#pragma once

#include <vector>
#include "Filme.hpp"
#include "ArrayList.hpp"
#include "TitleTypeFilter.hpp"
/*
void getTitleTypeFilter(ArrayList<Filme> filmes, ArrayList<TitleTypeFilter> &titlefilter,Genres titleType,
         ArrayList<int> &listaFinal, bool primeiroFiltro)
{
    std::vector<int> j;
    for(int i = 0; i < filmes.getSize(); i++)
    {
        if(filmes[i].titleType != titleType){
            titlefilter[i].isHere = false;
        }
        else{
            titlefilter[i].isHere = true;
            j.push_back(i);
        }
    }
    for(int i = 0; i < titlefilter.getSize(); i++)
    {
        if(primeiroFiltro){
                listaFinal[i] = j[i];
        }
        else{
            //if(titlefilter[i].isHere == false){
              //  lista.removeAt(i);
            //}
        }
    }
}
*/