#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "ArrayList.hpp"
#include "Cinema.hpp"
#include "Filme.hpp"

class Leitor
{
public:
    ArrayList<Filme> leitorFilmes(std::string nomeDoArquivo, Filme filmes);
};
