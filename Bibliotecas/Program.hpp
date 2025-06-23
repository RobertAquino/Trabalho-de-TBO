#pragma once

#include <iostream>

#include <vector>
#include <chrono>
#include <string>
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
        // Contador de tempo
        std::cout << "Iniciando o programa..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        // Lê os filmes e cinemas dos arquivos
        listaBaseFilmes = leitor.leitorFilmes(moviesFile);
        std::cout << "Filmes lidos: " << listaBaseFilmes.size() << std::endl;

        // Calcula o tempo de leitura dos filmes
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tempo de leitura dos filmes: " << duration.count() << " segundos" << std::endl;

        // Cria um HashMap para associar os filmes por ID
        HashMap<std::string, Filme> hashFilme;
        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];
            std::cout << "Adicionando filme: " << filme.getTConst() << std::endl;
            hashFilme.put(filme.getTConst(), filme);
        }
        std::cout << "HashMap de filmes criado com sucesso." << std::endl;
        listaBaseCinemas = leitor.leitorCinema(cinemasFile, hashFilme);
        std::cout << "Cinemas lidos: " << listaBaseCinemas.size() << std::endl;

        // Calcula o tempo de leitura dos cinemas
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Tempo de leitura dos cinemas: " << duration.count() << " segundos" << std::endl;
    }
    ~Program() = default;

    // Ponto de partida para o programa
    // void run();

    void test()
    {
        std::cin.get();
    }
};