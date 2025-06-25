#pragma once

#include <iostream>

#include <vector>
#include <chrono>
#include <string>
#include <climits>
#include <cctype>
#include "Filme.hpp"
#include "Leitor.hpp"
#include "SistemaDeFiltro.hpp"

class Program
{

private:
    std::vector<Filme> listaBaseFilmes;
    std::vector<Cinema> listaBaseCinemas;
    HashMap<std::string, Filme *> *hashFilme = nullptr;
    Leitor leitor;

    HashSet<int> idsFilmes;
    HashSet<int> idsCinemas;
    HashMap<Genres, std::vector<int>> filmesPorGenero;
    HashMap<TitleType, std::vector<int>> filmesPorTitleType;
    IntervalTreeDuration filmesPorDuracao;
    IntervalTreeYear filmesPorYear;

    SistemaDeFiltro *sistemaDeFiltro = nullptr;

    void populate()
    {
        // std::cout << listaBaseFilmes.size() << " filmes na lista base." << std::endl;

        for (int i = 0; i < listaBaseCinemas.size(); ++i)
        {
            for (auto &filmeCpy : listaBaseCinemas[i].filmesEmExibicao)
            {
                if (filmeCpy)
                {
                    filmeCpy->cinemasIds.push_back(i);
                }
                else
                {
                    std::cerr << "Aviso: Filme em exibicao no cinema " << i << " eh nulo.\n";
                }
            }
        }

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

        for (int i = 0; i < listaBaseCinemas.size(); ++i)
        {
            idsCinemas.put(i);
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
        hashFilme = new HashMap<std::string, Filme *>(listaBaseFilmes.size());
        for (int i = 0; i < listaBaseFilmes.size(); ++i)
        {
            Filme &filme = listaBaseFilmes[i];
            // std::cout << "Adicionando filme: " << filme.getTConst() << std::endl;
            hashFilme->put(filme.getTConst(), &filme);
        }
        // std::cout << "HashMap de filmes criado com sucesso." << std::endl;
        listaBaseCinemas = leitor.leitorCinema(cinemasFile, *hashFilme);
        // std::cout << "Cinemas lidos: " << listaBaseCinemas.size() << std::endl;

        // Calcula o tempo de leitura dos cinemas
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        // td::cout << "Tempo de leitura dos cinemas: " << duration.count() << " segundos" << std::endl;
    }
    ~Program()
    {
        delete hashFilme;
    }

    // Ponto de partida para o programa
    void run()
    {
        std::cout << "Iniciando carregamento..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        populate();
        std::cout << "Caregamento concluido." << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::chrono::duration<double> totalDuration = std::chrono::duration<double>(0);
        std::cout << "Tempo de carregamento dos HashMaps: " << duration.count() << " segundos" << std::endl;

        std::string expressao;
        bool isRunning = true;
        while (isRunning)
        {
            int opc;
            std::cout << "Selecione a opcao desejada: \n\t1 - Buscar por filmes"
                      << "\n\t2 - Buscar por Cinemas\n\t0 - Sair do programa\nOPCAO: ";
            std::cin >> opc;
            if (opc == 0)
            {
                break;
            }
            std::cout
                << "Digite a expressao de filtro: ";
            std::cin.ignore();
            std::getline(std::cin, expressao);

            std::cout << "Criando arvore de expressao...";
            start = std::chrono::high_resolution_clock::now();
            sistemaDeFiltro = new SistemaDeFiltro(expressao, &listaBaseFilmes, &listaBaseCinemas,
                                                  &filmesPorYear, &filmesPorDuracao, filmesPorGenero,
                                                  filmesPorTitleType);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            totalDuration += duration;
            std::cout << "Tempo de criacao da arvore de expressao: " << duration.count() << " segundos" << std::endl;

            std::cout << "Inicando filtragem...";
            start = std::chrono::high_resolution_clock::now();
            HashSet<int> resultado = sistemaDeFiltro->filtrar(idsFilmes, idsCinemas);
            std::vector<int> ids = resultado.getAll();
            end = std::chrono::high_resolution_clock::now();
            delete sistemaDeFiltro;

            duration = end - start;
            totalDuration += duration;
            std::cout << "Tempo de busca: " << duration.count() << " segundos" << std::endl;
            if (opc == 1)
            {
                searchMovies(ids);
            }
            else
            {
                searchCinemas(ids);
            }

            std::cout << std::endl;
        }
    }

    void searchMovies(const std::vector<int> &idFilmes)
    {
        int qtdFilmes = idFilmes.size();
        if (qtdFilmes == 0)
        {
            std::cout << "Nenhum filme encontrado.\n";
            return;
        }
        else
        {
            std::cout << "Foram encontrados " << qtdFilmes << " filmes.\n";
        }

        std::cout << "Deseja exibir-los? (S/N): ";
        char opc;
        std::cin >> opc;
        opc = tolower(opc);
        if (opc == 's')
        {
            for (int id : idFilmes)
            {
                Filme &filme = listaBaseFilmes[id];
                std::cout << "Filme: " << filme.getTConst() << " - " << filme.getPrimaryTitle() << std::endl;
            }
        }
    }

    void searchCinemas(const std::vector<int> &idCinemas)
    {
        int qtdCinemas = idCinemas.size();
        if (qtdCinemas == 0)
        {
            std::cout << "Nenhum cinema encontrado.\n";
            return;
        }
        else
        {
            std::cout << "Foram encontrados " << qtdCinemas << " cinemas.\n";
        }

        std::cout << "Deseja exibir-los? (S/N): ";
        char opc;
        std::cin >> opc;
        opc = tolower(opc);
        if (opc == 's')
        {
            for (int id : idCinemas)
            {
                Cinema &cinema = listaBaseCinemas[id];
                std::cout << "Cinema: " << cinema.cinemaId << " - " << cinema.nomeCinema << std::endl;
            }
        }
    }
};

/*    void test()
    {
        // std::cout << "Iniciando testes..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        populate();
        // std::cout << "População dos HashMaps concluída." << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        // std::cout << "Tempo de população dos HashMaps: " << duration.count() << " segundos" << std::endl;

        std::string expressao = "#g{horror}&!(#a{1800,000})";
        // std::cout << "Filtro:" + expressao << std::endl;
        // std::cout << "Filtrando filmes..." << std::endl;
        sistemaDeFiltro = new SistemaDeFiltro(expressao, &listaBaseFilmes, &listaBaseCinemas, &filmesPorYear, &filmesPorDuracao, filmesPorGenero, filmesPorTitleType);
        // std::cout << "Sistema de filtro criado com sucesso." << std::endl;
        HashSet<int> resultado = sistemaDeFiltro->filtrar(idsFilmes, idsCinemas);
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
        if (ids.size() <= 500)
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

*/