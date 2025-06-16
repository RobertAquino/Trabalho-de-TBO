#pragma once

#include "ArrayList.hpp"
#include "TitleTypeFilter.hpp"
#include "Filme.hpp"
#include "Cinema.hpp"

class CinemaTitleTypeFilter
{
public:
    bool isHere;

    void getCinemaTitleTypeFilter(ArrayList<Cinema> cinemas, ArrayList<TitleTypeFilter> &titlefilter, Genres titleType,
                                  ArrayList<int> &listaFinal, bool primeiro);
}