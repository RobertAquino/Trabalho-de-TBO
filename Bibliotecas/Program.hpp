#pragma once

#include <iostream>

#include <vector>
#include "Filme.hpp"
#include "Leitor.hpp"
#include "SistemaDeFiltro.hpp"

class Program
{

private:
    std::vector<Filme> listaBaseFilmes;
    std::vector<Cinema> listaBaseCinemas;
    Leitor leitor;

    HashMap<Genres, std::vector<Filme>> filmesPorGenero;
    HashMap<TitleType, std::vector<Filme>> filmesPorTitleType;
    HashMap<int, std::vector<Filme>> filmesPorDuracao;
    HashMap<int, std::vector<Filme>> filmesPorAno;
    SistemaDeFiltro *sistemaDeFiltro = nullptr;

    void populate()
    {
        // TODO
    }

public:
    Program(const std::string &moviesFile, const std::string &cinemasFile)
    {
        // Lê os filmes e cinemas dos arquivos
        listaBaseFilmes = leitor.leitorFilmes(moviesFile);

        // Cria um HashMap para associar os filmes por ID
        HashMap<std::string, Filme> hashFilme;
        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];
            hashFilme.put(filme.getTConst(), filme);
        }
        listaBaseCinemas = leitor.leitorCinema(cinemasFile, hashFilme);
    }
    ~Program();

    // Ponto de partida para o programa
    void run();
};