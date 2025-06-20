#include "../Bibliotecas/FiltroTitleType.hpp"

FiltroTitleType::FiltroTitleType(TitleType titleType, HashMap<TitleType, ArrayList<int>> &baseFilmes)
    : titleType(titleType), baseFilmes(baseFilmes) {}

HashSet<int> FiltroTitleType::aplicar()
{
    HashSet<int> result;

    if (baseFilmes.containsKey(titleType))
    {
        std::optional<ArrayList<int>> filmesOpt = baseFilmes.get(titleType);
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