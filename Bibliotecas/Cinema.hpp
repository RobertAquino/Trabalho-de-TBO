#pragma once

#include <string>
#include <sstream>
#include "Filme.hpp"
#include <vector>
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
    std::vector<Filme> filmesEmExibicao;

    Cinema() = default;
    Cinema(const std::string &cinemaId_str, const std::string nomeCinema_str, const std::string coordenadaX_str, const std::string coordenadaY_str,
           const std::string &precoIngresso_str, const std::string filmesEmExibicao_str, HashMap<std::string, Filme> &hashFilme)
    {
        cinemaId = cinemaId_str;
        nomeCinema = nomeCinema_str;
        localizacao = Localizacao(std::stoi(coordenadaX_str), std::stoi(coordenadaY_str));
        precoIngresso = std::stod(precoIngresso_str);

        // Divide os IDs dos filmes
        std::stringstream ss_filmes(filmesEmExibicao_str);
        std::string idfilmeIndividual = "";

        while (std::getline(ss_filmes, idfilmeIndividual, ','))
        {
            idfilmeIndividual.erase(0, idfilmeIndividual.find_first_not_of(" \n\r\t"));
            idfilmeIndividual.erase(idfilmeIndividual.find_last_not_of(" \n\r\t") + 1);
            std::optional<Filme> filmeEncontrado = hashFilme.get(idfilmeIndividual);
            if (filmeEncontrado.has_value())
            {
                filmesEmExibicao.push_back(filmeEncontrado.value());
            }
        }
    }
    ~Cinema() = default;
};