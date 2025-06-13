#pragma once

#include "Filme.hpp"
#include "ArrayList.hpp"

class genresFilter
{
    public:

    ArrayList<Filme> genresFilter;

    ArrayList<Filme> getGenresFilter(ArrayList<Filme> filmes, ArrayList<Filme> &genresFilter);

};  

    ArrayList<Filme> getGenresFilter(ArrayList<Filme> filmes, ArrayList<Filme> &genresFilter, Genres genre)
    {
        ArrayList<Filme> filme;   
    }