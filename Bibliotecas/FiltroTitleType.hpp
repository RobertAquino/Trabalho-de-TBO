#pragma ocen

#include "Filtro.hpp"

class FiltroTitleType : public Filtro
{
private:
    TitleType titleType;
    HashMap<TitleType, ArrayList<int>> &baseFilmes;

public:
    FiltroTitleType(TitleType titleType, HashMap<TitleType, ArrayList<int>> &baseFilmes);

    HashSet<int> aplicar() override;
};