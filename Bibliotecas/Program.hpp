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
    IntervalTreeDuration filmesPorDuracao;
    IntervalTreeYear filmesPorYear;

    SistemaDeFiltro *sistemaDeFiltro = nullptr;

    void populate()
    {
        // std::cout << listaBaseFilmes.size() << " filmes na lista base." << std::endl;

        // Verifica se a lista de filmes está vazia
        if (listaBaseFilmes.empty())
        {
            std::cerr << "Erro: listaBaseFilmes está vazia. Verifique a leitura do arquivo de filmes." << std::endl;
            return;
        }

        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];
            // std::cout << "Processando filme: " << filme.getTConst() << " - " << filme.getPrimaryTitle() << std::endl;

            filmesPorYear.insertNode(&filmesPorYear.root, listaBaseFilmes, i);
            filmesPorDuracao.insertNode(&filmesPorDuracao.root, listaBaseFilmes, i);

            // Adiciona o ID do filme ao HashSet
            idsFilmes.put(i);

            // Processa os gêneros do filme
            std::vector<Genres> generos = filme.getGenres();
            for (Genres &genre : generos)
            {
                // std::cout << "Adicionando gênero: " << static_cast<int>(genre) << " ao filme: " << filme.getTConst() << std::endl;
                if (!filmesPorGenero.containsKey(genre))
                {
                    // std::cout << "Criando novo vetor para gênero: " << static_cast<int>(genre) << std::endl;
                    std::vector<int> emptyVector;
                    filmesPorGenero.put(genre, emptyVector);
                }
                filmesPorGenero.get(genre).value().get().push_back(i);
                // std::cout << "Tamanho do vetor para gênero " << static_cast<int>(genre) << ": "
                //<< filmesPorGenero.get(genre).value().size() << std::endl;
            }

            // Processa o TitleType
            TitleType titleType = strToTitleType(filme.getTitleType());
            // std::cout << "TitleType: " << filme.getTitleType() << " convertido para: " << static_cast<int>(titleType) << std::endl;
            if (!filmesPorTitleType.containsKey(titleType))
            {
                // std::cout << "Criando novo vetor para TitleType: " << filme.getTitleType() << std::endl;
                std::vector<int> emptyVector;
                filmesPorTitleType.put(titleType, emptyVector);
            }
            filmesPorTitleType.get(titleType).value().get().push_back(i);
            //::cout << "Tamanho do vetor para TitleType " << filme.getTitleType() << ": "
            //<< filmesPorTitleType.get(titleType).value().size() << std::endl;
        }

        // std::cout << "População dos HashMaps concluída." << std::endl;
        // std::cout << filmesPorGenero.getSize() << " gêneros distintos encontrados." << std::endl;
    }

public:
    Program(const std::string &moviesFile, const std::string &cinemasFile)
    {
        // Contador de tempo
        // std::cout << "Iniciando o programa..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        // Lê os filmes e cinemas dos arquivos
        listaBaseFilmes = leitor.leitorFilmes(moviesFile);
        // std::cout << "Filmes lidos: " << listaBaseFilmes.size() << std::endl;

        // Calcula o tempo de leitura dos filmes
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        // std::cout << "Tempo de leitura dos filmes: " << duration.count() << " segundos" << std::endl;

        // Cria um HashMap para associar os filmes por ID
        HashMap<std::string, Filme> hashFilme(listaBaseFilmes.size());
        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];
            // std::cout << "Adicionando filme: " << filme.getTConst() << std::endl;
            hashFilme.put(filme.getTConst(), filme);
        }
        // std::cout << "HashMap de filmes criado com sucesso." << std::endl;
        listaBaseCinemas = leitor.leitorCinema(cinemasFile, hashFilme);
        // std::cout << "Cinemas lidos: " << listaBaseCinemas.size() << std::endl;

        // Calcula o tempo de leitura dos cinemas
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        // td::cout << "Tempo de leitura dos cinemas: " << duration.count() << " segundos" << std::endl;
    }
    ~Program() = default;

    // Ponto de partida para o programa
    // void run();

    void test()
    {
        // std::cout << "Iniciando testes..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        populate();
        // std::cout << "População dos HashMaps concluída." << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        // std::cout << "Tempo de população dos HashMaps: " << duration.count() << " segundos" << std::endl;

        std::string expressao = "#a{2012,2012}";
        // std::cout << "Filtro:" + expressao << std::endl;
        // std::cout << "Filtrando filmes..." << std::endl;
        sistemaDeFiltro = new SistemaDeFiltro(expressao, &filmesPorYear, &filmesPorDuracao, filmesPorGenero, filmesPorTitleType);
        // std::cout << "Sistema de filtro criado com sucesso." << std::endl;
        HashSet<int> resultado = sistemaDeFiltro->filtrar(idsFilmes);
        std::vector<int> ids = resultado.getAll();
        if (ids.empty())
        {
            std::cout << "Nenhum filme encontrado com o filtro: " << expressao << std::endl;

            // std::cout << "E lista esperado: " << std::endl;
            // std::cout << "Quantidade de Filmes do gênero Adventure: " << filmesPorGenero.get(Genres::Adventure).value().get().size() << std::endl;
        }
        else
        {
            std::cout << "Quantidade de filmes encontrados com o filtro (" << expressao << "): " << ids.size() << std::endl;
        }
        if (ids.size() <= 150)
        {
            for (int id : ids)
            {
                Filme &filme = listaBaseFilmes[id];
                std::cout << "Filme: " << filme.getTConst() << " - " << filme.getPrimaryTitle() << std::endl;
            }
        }
        std::cin.get();
    }

    void test2()
    {
        HashMap<Genres, std::vector<int>> testMap;
        testMap.put(Genres::Adventure, std::vector<int>());
        testMap.get(Genres::Adventure).value().get().push_back(1);
        testMap.get(Genres::Adventure).value().get().push_back(3);
        testMap.get(Genres::Adventure).value().get().push_back(5);
        std::cout << testMap.get(Genres::Adventure).value().get().size() << std::endl; // Deve imprimir 1
        for (int id : testMap.get(Genres::Adventure).value().get())
        {
            std::cout << "ID do filme: " << id << std::endl; // Deve imprimir 1, 3, 5
        }
    }
};
