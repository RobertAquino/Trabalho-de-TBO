#pragma once

#include <vector>
#include "Filtro.hpp"

class FiltroTitleType : public Filtro
{
private:
    TitleType titleType;
    HashMap<TitleType, std::vector<int>> &baseFilmes;

public:
    FiltroTitleType(TitleType titleType, HashMap<TitleType, std::vector<int>> &baseFilmes)
        : titleType(titleType), baseFilmes(baseFilmes) {}

    HashSet<int> aplicar() override
    {
        HashSet<int> result;

        if (baseFilmes.containsKey(titleType))
        {
            std::optional<std::vector<int>> filmesOpt = baseFilmes.get(titleType);
            if (filmesOpt.has_value())
            {
                for (int i = 0; i < filmesOpt->size(); ++i)
                {
                    result.put((*filmesOpt)[i]);
                }
            }
        }
        return result;
    }
};
