#pragma once

#include <iostream>

#include <vector>
#include "Filme.hpp"
#include "Leitor.hpp"

class Program
{
public:
    Program(const std::string &moviesFile, const std::string &cinemasFile);
    ~Program();

    // Ponto de partida para o programa
    void run();

private:
    std::vector<Filme> listaBaseFilmes;
    std::vector<Cinema> listaBaseCinemas;
    Leitor leitor;

    void populate();

        // ...
};