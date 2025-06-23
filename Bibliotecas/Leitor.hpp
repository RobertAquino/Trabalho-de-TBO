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
    static std::vector<Filme> leitorFilmes(const std::string &nomeDoArquivo);
    static std::vector<Cinema> leitorCinema(const std::string &nomeDoArquivo,
                                            HashMap<std::string, Filme> &hashFilme);
};
