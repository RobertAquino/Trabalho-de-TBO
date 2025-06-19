#include "../Bibliotecas/Program.hpp"
#include "../Bibliotecas/HashMap.hpp"
#include "../Bibliotecas/ArrayList.hpp"
#include "../Bibliotecas/Filtro.hpp"
#include "../Bibliotecas/FiltroGenero.hpp"

Program::Program(const std::string &moviesFile, const std::string &cinemasFile) /* : leitor(moviesFile, cinemasFile)  */
{
}

Program::~Program()
{
}

void Program::run()
{
    bool programRunning = true;

    // Usa o leitor para popular filmeBase;
    populate();

    // Loop principal
    while (programRunning)
    {
    }
}