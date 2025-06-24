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

    HashSet<int> idsFilmes;
    HashMap<Genres, std::vector<int>> filmesPorGenero;
    HashMap<TitleType, std::vector<int>> filmesPorTitleType;
    HashMap<int, std::vector<Filme>> filmesPorDuracao;
    HashMap<int, std::vector<Filme>> filmesPorAno;
    SistemaDeFiltro *sistemaDeFiltro = nullptr;

    void populate()
    {

        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];

            idsFilmes.put(i);
            for (Genres &genre : filme.getGenres())
            {
                // std::cout << "Adicionando genero: " << genero << " ao filme: " << filme.getTConst() << std::endl;
                if (!filmesPorGenero.containsKey(genre))
                {
                    // std::cout << "Adicionando genero: " << genero << std::endl;
                    filmesPorGenero.put(genre, std::vector<int>());
                }
                // std::cout << "Adicionando filme: " << filme.getTConst() << " ao genero: " << genero << std::endl;
                filmesPorGenero.get(genre).value().push_back(i);
            }

            TitleType titleType = strToTitleType(filme.getTitleType());
            if (!filmesPorTitleType.containsKey(titleType))
            {
                // std::cout << "Adicionando titleType: " << filme.getTitleType() << std::endl;
                filmesPorTitleType.put(titleType, std::vector<int>());
            }
            // std::cout << "Adicionando filme: " << filme.getTConst()
            //           << " ao titleType: " << filme.getTitleType() << std::endl;
            filmesPorTitleType.get(titleType).value().push_back(i);
        }
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
        HashMap<std::string, Filme> hashFilme(listaBaseFilmes.size());
        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];
            // std::cout << "Adicionando filme: " << filme.getTConst() << std::endl;
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
        std::cout << "Iniciando testes..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        populate();
        std::cout << "População dos HashMaps concluída." << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tempo de população dos HashMaps: " << duration.count() << " segundos" << std::endl;

        std::string expressao = "#g{adventure}";
        std::cout << "Filtro:" + expressao << std::endl;
        std::cout << "Filtrando filmes..." << std::endl;
        sistemaDeFiltro = new SistemaDeFiltro(expressao, filmesPorGenero, filmesPorTitleType);
        std::cout << "Sistema de filtro criado com sucesso." << std::endl;
        HashSet<int> resultado = sistemaDeFiltro->filtrar(idsFilmes);
        std::vector<int> ids = resultado.getAll();
        for (int id : ids)
        {
            Filme &filme = listaBaseFilmes[id];
            std::cout << "Filme: " << filme.getTConst() << " - " << filme.getPrimaryTitle() << std::endl;
        }
        std::cin.get();
    }
};