#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Cinema.hpp"
#include "Filme.hpp"
#include "HashMap.hpp"
#include <vector>

class Leitor
{
public:
    std::vector<Filme> leitorFilmes(std::string nomeDoArquivo);
    std::vector<Cinema> leitorCinema(std::string nomeDoArquivo, HashMap<std::string, Filme> &hashFilme);
};
