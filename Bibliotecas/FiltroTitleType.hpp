#pragma once

#include <vector>
#include "Filtro.hpp"

class FiltroTitleType : public Filtro
{
private:
    TitleType titleType;
    HashMap<TitleType, std::vector<int>> &baseFilmes;

public:
    FiltroTitleType(TitleType titleType, HashMap<TitleType, std::vector<int>> &baseFilmes);

    HashSet<int> aplicar() override;
};