#pragma once

#include "ArrayList.hpp"
#include "Cinema.hpp"
#include <iostream>
#include <sstream>

enum class Genres
{
    Action = 0,
    Adventure = 1,
    Animation = 2,
    Biography = 3,
    Comedy = 4,
    Crime = 5,
    Documentary = 6,
    Drama = 7,
    Family = 8,
    Fantansy = 9,
    Game_Show = 10,
    History = 11,
    Horror = 12,
    Music = 13,
    Music = 14,
    Musicial = 15,
    Mystery = 16,
    News = 17,
    Reality_Tv = 18,
    Romance = 19,
    Sci_fi = 20,
    Short = 21,
    Sport = 22,
    Talk_Show = 23,
    Thriller = 24,
    War = 25,
    Adult = 26
};

enum class TitleType
{
    movie = 0,
    shortFilm = 1,
    tvSeries = 2,
    tvEpisode = 3,
    tvMiniSeries = 4,
    video = 5,
    videoGame = 6,
    tvMovie = 7,
    tvSpecial = 8,
    tvShort = 9
};

class Filme
{
public:
    Cinema cinema;
    std::string tConst;
    std::string titleType;    // Mudar para enum TitleType
    std::string primaryGenre; // Mudar para enum Genres
    std::string primaryTitle;
    std::string originalTitle;
    bool isAdult;
    short startYear;
    short endYear;
    int runTimesMinutes;
    ArrayList<std::string> genres;

    Filme(const std::string &tconst_str, const std::string &type_str, const std::string &pTitle_str,
          const std::string &oTitle_str, const std::string &isAdult_str, const std::string &startYear_str,
          const std::string &endYear_str, const std::string &runtime_str, const std::string &genres_str)
    {
        tConst = tconst_str;
        titleType = type_str;
        primaryTitle = pTitle_str;
        originalTitle = oTitle_str;
        std::stringstream ss_genres(genres_str);
        std::string genero_individual;

        /* O laço lê a stringstream até não haver mais o que ler,
         usando a vírgula ',' como o caractere delimitador*/
        while (std::getline(ss_genres, genero_individual, ','))
        {
            /// Adiciona cada gênero encontrado na ArrayList
            genres.add(genero_individual);
        }

        // ---- Lógica para tratar o '\N' e converter para número ----
        // Se a string for "\\N", 0 sera o valor padrão, caso ao contraio o valor sera lido.
        // "\\N" em vez de "\N" no código pois a primeira '\' é um caractere de escape.

        isAdult = (isAdult_str == "\\N") ? 0 : std::stoi(isAdult_str);
        startYear = (startYear_str == "\\N") ? 0 : std::stoi(startYear_str);
        endYear = (endYear_str == "\\N") ? 0 : std::stoi(endYear_str);
        runTimesMinutes = (runtime_str == "\\N") ? 0 : std::stoi(runtime_str);
    }

    ~Filme();
    void transformaString();

    Cinema getCinema()
    {
        return cinema;
    }
    void setCinema(Cinema cinema)
    {
        this->cinema = cinema;
    }

    std::string getTConst()
    {
        return tConst;
    }
    void setTConst(std::string tConst)
    {
        this->tConst = tConst;
    }

    std::string getTitleType()
    {
        return titleType;
    }
    void setTitleType(std::string titleType)
    {
        this->titleType = titleType;
    }

    std::string getPrimaryTitle()
    {
        return primaryTitle;
    }
    void setPrimaryTitle(std::string primaryTitle)
    {
        this->primaryTitle = primaryTitle;
    }

    std::string getOriginalTitle()
    {
        return originalTitle;
    }
    void setOriginalTitle(std::string originalTitle)
    {
        this->originalTitle = originalTitle;
    }

    bool getIsAdult()
    {
        return isAdult;
    }
    void setIsAdult(bool isAdult)
    {
        this->isAdult = isAdult;
    }

    short getStartYear()
    {
        return startYear;
    }
    void setStartYear(short startYear)
    {
        this->startYear = startYear;
    }

    short getEndYear()
    {
        return endYear;
    }
    void setEndYear(short endYear)
    {
        this->endYear = endYear;
    }

    int getRunTimesMinutes()
    {
        return runTimesMinutes;
    }
    void setRunTimesMinutes(int runTimesMinutes)
    {
        this->runTimesMinutes = runTimesMinutes;
    }

    ArrayList<std::string> getGenres()
    {
        return genres;
    }
    void setGenres(const ArrayList<std::string> &genres)
    {
        this->genres = genres;
    }
};
