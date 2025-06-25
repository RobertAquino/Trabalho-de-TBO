#pragma o

#include "Filtro.hpp"
#include <vector>

class FiltroGenero : public Filtro
{
private:
    Genres genre;
    HashMap<Genres, std::vector<int>> &baseFilmes;

public:
    FiltroGenero(Genres genre, HashMap<Genres, std::vector<int>> &baseFilmes);

    HashSet<int> aplicar() override;
};