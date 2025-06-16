#pragma once

#include <vector>
#include "Filme.hpp"
#include "ArrayList.hpp"

enum class titleType
{
    Short = 0,
    tvEpisode = 1,
    video = 2,
    movie = 3,
    tvSeries = 4
};
class TitleTypeFilter
{
public:
    bool isHere;

    void getTitleTypeFilter(ArrayList<Filme> filmes, ArrayList<TitleTypeFilter> &titlefilter, Genres titleType,
<<<<<<< HEAD
                            ArrayList<int> &lista, bool primeiro);
=======
                            ArrayList<int> &lista, bool primeiroFiltro);
>>>>>>> 49f897e3945a7c041e6f8ee0989e15f4edaa44c4
};
