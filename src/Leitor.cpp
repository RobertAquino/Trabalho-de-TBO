#include <sstream>
#include "../Bibliotecas/Leitor.hpp"

std::vector<Filme> leitorFilmes(std::string &nomeDoArquivo)
{
    std::ifstream arquivo(nomeDoArquivo);
    std::vector<Filme> catalogo;
    if (!arquivo)
    {
        std::cout << "Não foi posivel abrir o arquivo" << std::endl;
        return catalogo;
    }

    std::string linha;
    std::getline(arquivo, linha); // Ignora o cabeçalho

    // Primeiro, usa o getline para ler o arquivo e pegar a linha inteira, que fica armazenada em uma única string, assim: "tt7917518\tshort\tThe Battle II\t...etc"
    while (std::getline(arquivo, linha))
    {
        // stringstream permite "quebrar" a string
        std::stringstream ss(linha);
        std::string tconst, type, pTitle, oTitle, isAdult, startYear, endYear, runtime, genres;

        // Extrai todos os campos como strings
        std::getline(ss, tconst, '\t');
        std::getline(ss, type, '\t');
        std::getline(ss, pTitle, '\t');
        std::getline(ss, oTitle, '\t');
        std::getline(ss, isAdult, '\t');
        std::getline(ss, startYear, '\t');
        std::getline(ss, endYear, '\t');
        std::getline(ss, runtime, '\t');
        std::getline(ss, genres, '\t');

        // Cria o objeto do Filme
        Filme filmeAtual(tconst, type, pTitle, oTitle, isAdult, startYear, endYear, runtime, genres);
        catalogo.push_back(filmeAtual);
    }
    arquivo.close();
    return catalogo;
}

std::vector<Cinema> leitorCinema(std::string &nomeDoArquivo, HashMap<std::string, Filme> &hashFilme)
{
    std::ifstream arquivo(nomeDoArquivo);
    std::vector<Cinema> cinemas;
    if (!arquivo)
    {
        std::cout << "Não foi posivel abrir o arquivo" << std::endl;
        return cinemas;
    }

    std::string linha;
    std::getline(arquivo, linha);
    while (std::getline(arquivo, linha))
    {
        std::stringstream ss(linha);
        std::string cinemaid, nomeCinema, x, y, precoIngresso, filmes;

        std::getline(ss, cinemaid, ',');
        std::getline(ss, nomeCinema, ',');
        std::getline(ss, x, ',');
        std::getline(ss, y, ',');
        std::getline(ss, precoIngresso, ',');
        std::getline(ss, filmes); // Lê o resto da linha

        Cinema cinemaAtual(cinemaid, nomeCinema, x, y, precoIngresso, filmes, hashFilme);
        cinemas.push_back(cinemaAtual);
    }
    arquivo.close();
    return cinemas;
}
