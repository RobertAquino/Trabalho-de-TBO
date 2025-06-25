#pragma once

#include "Filtro.hpp"
#include <vector>

class FiltroGenero : public Filtro
{
private:
    Genres genre;
    HashMap<Genres, std::vector<int>> &baseFilmes;

public:
    FiltroGenero(Genres genre, HashMap<Genres, std::vector<int>> &baseFilmes) : genre(genre), baseFilmes(baseFilmes) {}

    HashSet<int> aplicar() override
    {
        HashSet<int> result;

        if (baseFilmes.containsKey(genre))
        {
            std::optional<std::vector<int>> filmesOpt = baseFilmes.get(genre);
            if (filmesOpt.has_value())
            {
                for (int i = 0; i < filmesOpt->size(); ++i)
                {
                    result.put((*filmesOpt)[i]);
                }
            }
        }
        if (result.getSize() == 0)
        {
            std::cout << "Nenhum filme encontrado para o gênero especificado." << std::endl;
        }

        return result;
    }
};