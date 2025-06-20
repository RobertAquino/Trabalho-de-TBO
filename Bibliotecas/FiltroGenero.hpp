#pragma ocen

#include "Filtro.hpp"

class FiltroGenero : public Filtro
{
private:
    Genres genre;
    HashMap<Genres, ArrayList<int>> &baseFilmes;

public:
    FiltroGenero(Genres genre, HashMap<Genres, ArrayList<int>> &baseFilmes);

    HashSet<int> aplicar() override;
};