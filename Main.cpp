#include <iostream>
#include "Bibliotecas/Program.hpp"

int main()
{
    Program program("DataBase/filmesCrop.txt", "DataBase/cinemas.txt");
    program.test();

    return 0;
}
