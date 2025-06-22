#include "../Bibliotecas/FiltroTitleType.hpp"
#include <vector>

FiltroTitleType::FiltroTitleType(TitleType titleType, HashMap<TitleType, std::vector<int>> &baseFilmes)
    : titleType(titleType), baseFilmes(baseFilmes) {}

HashSet<int> FiltroTitleType::aplicar()
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