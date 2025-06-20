#pragma once

#include "Filme.hpp"
#include "ArrayList.hpp"
#include "Localizacao.hpp"
#include "HashMap.hpp"
#include <iostream>

class Cinema
{
public:
    std::string cinemaId;
    std::string nomeCinema;
    Localizacao localizacao;
    double precoIngresso;
    ArrayList<Filme> filmesEmExibicao;

    Cinema() = default;
    Cinema(const std::string &cinemaId_str, const std::string nomeCinema_str, const std::string coordenadaX_str, const std::string coordenadaY_str,
           const std::string &precoIngresso_str, const std::string filmesEmExibicao_str, HashMap<std::string, Filme> &hashFilme)
    {
        cinemaId = cinemaId_str;
        nomeCinema = nomeCinema_str;
        localizacao = Localizacao(stoi(coordenadaX_str), stoi(coordenadaY_str));
        precoIngresso = stoi(precoIngresso_str);

        // Divide os IDs dos filmes
        std::stringstream ss_filmes(filmesEmExibicao_str);
        std::string IdfilmeIndividual;
        while (std::getline(ss_filmes, IdfilmeIndividual, ','))
        {
            std::optional<Filme> filmeEncontrado = hashFilme.get(IdfilmeIndividual);
            filmesEmExibicao.add(filmeEncontrado.value());
        }
    }
    ~Cinema();
};