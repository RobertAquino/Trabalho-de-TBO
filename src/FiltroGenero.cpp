#include "../Bibliotecas/FiltroGenero.hpp"

FiltroGenero::FiltroGenero(Genres genre, HashMap<Genres, ArrayList<int>> &baseFilmes)
    : genre(genre), baseFilmes(baseFilmes)
{
}

HashSet<int> FiltroGenero::aplicar()
{
    HashSet<int> result;

    if (baseFilmes.containsKey(genre))
    {
        std::optional<ArrayList<int>> filmesOpt = baseFilmes.get(genre);
        if (filmesOpt.has_value())
        {
            for (int i = 0; i < filmesOpt->getSize(); ++i)
            {
                result.put((*filmesOpt)[i]);
            }
        }
    }

    return result;
}