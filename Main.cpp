#include <iostream>
#include "Bibliotecas/Program.hpp"

int main()
{
    std::string moviesFile = "DataBase/filmesCrop.txt";
    std::string cinemasFile = "DataBase/cinemas.txt";
    Program program(moviesFile, cinemasFile);
    program.test();

    return 0;
}
