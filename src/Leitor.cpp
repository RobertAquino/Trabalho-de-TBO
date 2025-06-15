#pragma once

#include <sstream>
#include "../Bibliotecas/Leitor.hpp"

ArrayList<Filme> leitorFilmes(std::string nomeDoArquivo)
{
    std::ifstream arquivo(nomeDoArquivo);
    ArrayList<Filme> catalogo;
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
        /* Depois, coloca essa string em um stringstream.isso nos permite usar getline uma segunda vez, mas agora para extrair cada campo individualmente,
        usando o caractere de tabulação (\t) como separador,a cada chamada, um campo é lido e guardado em uma variável
        ao final, quando todos os campos foram separados, o objeto Filme é criado com essas informações */
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
        catalogo.add(filmeAtual);
    }
    arquivo.close();
    return catalogo; // Retorna o catálogo preenchido
}
