#pragma ocen

#include "Filtro.hpp"

class FiltroGenero : public Filtro
{
private:
    std::string genre;

public:
    FiltroGenero(const std::string &genre);

    ArrayList<Filme> aplicar(const ArrayList<Filme> &filmes) const override;
};