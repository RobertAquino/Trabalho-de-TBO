#pragma once

#include <iostream>

#include "ArrayList.hpp"
#include "Filme.hpp"
#include "SistemaDeFiltro.hpp"

class Program {
public:
    Program(const std::string &moviesFile, const std::string &cinemasFile);
    ~Program();

    // Ponto de partida para o programa
    void run();
private:
    ArrayList<Filme> listaBaseFilmes;
    // Leitor leitor; -> construtor(const std::string &moviesFile, const std::string &cinemasFile)

    // Lê os documentos do diretório informado e popula a listaBaseFilmes com o conteúdo lido.
    void populate(); 

    // ...
};