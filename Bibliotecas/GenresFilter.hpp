#pragma once

#include "Filme.hpp"
#include "ArrayList.hpp"

class genresFilter
{
    public:

    ArrayList<Filme> genresFilter;

    void getGenresFilter(const ArrayList<Filme> &filmes, ArrayList<int> &genresFilter, Genres genre);

};  

    void getGenresFilter(const ArrayList<Filme> &filmes, ArrayList<int> &genresFilter, Genres genre)
    {
        for(int i = 0; i < genresFilter.getSize(); i++)
        {
            if(genresFilter[i] != genre) {
                genresFilter.removeAt(i);
                i--;
            }
        }
    }
    