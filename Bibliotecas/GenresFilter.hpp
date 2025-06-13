#pragma once

#include "Filme.hpp"
#include "ArrayList.hpp"

class genresFilter
{
    public:

    bool isHere;

    void getGenresFilter(const ArrayList<Filme> &filmes, ArrayList<int> &genresFilter, Genres genre, bool primeiro);

};  
