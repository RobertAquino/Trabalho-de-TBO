#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "ArrayList.hpp"
#include "Cinema.hpp"
#include "Filme.hpp"
#include "HashMap.hpp"

class Leitor
{
public:
    ArrayList<Filme> leitorFilmes(std::string nomeDoArquivo);
    ArrayList<Cinema> leitorCinema(std::string nomeDoArquivo, HashMap<std::string, Filme> &hashFilme);
};
