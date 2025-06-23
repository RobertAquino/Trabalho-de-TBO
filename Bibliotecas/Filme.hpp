#pragma once

#include <vector>
#include <string>
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
    Musicial = 14,
    Mystery = 15,
    News = 16,
    Reality_Tv = 17,
    Romance = 18,
    Sci_fi = 19,
    Short = 20,
    Sport = 21,
    Talk_Show = 22,
    Thriller = 23,
    War = 24,
    Adult = 25
};

static Genres strToGenre(const std::string &str)
{
    if (str == "action")
        return Genres::Action;
    else if (str == "adventure")
        return Genres::Adventure;
    else if (str == "animation")
        return Genres::Animation;
    else if (str == "biography")
        return Genres::Biography;
    else if (str == "comedy")
        return Genres::Comedy;
    else if (str == "crime")
        return Genres::Crime;
    else if (str == "documentary")
        return Genres::Documentary;
    else if (str == "drama")
        return Genres::Drama;
    else if (str == "family")
        return Genres::Family;
    else if (str == "fantasy")
        return Genres::Fantansy;
    else if (str == "game_show")
        return Genres::Game_Show;
    else if (str == "history")
        return Genres::History;
    else if (str == "horror")
        return Genres::Horror;
    else if (str == "music")
        return Genres::Music;
    else if (str == "musical")
        return Genres::Musicial;
    else if (str == "mystery")
        return Genres::Mystery;
    else if (str == "news")
        return Genres::News;
    else if (str == "reality_tv")
        return Genres::Reality_Tv;
    else if (str == "romance")
        return Genres::Romance;
    else if (str == "sci-fi")
        return Genres::Sci_fi;
    else if (str == "short")
        return Genres::Short;
    else if (str == "sport")
        return Genres::Sport;
    else if (str == "talk_show")
        return Genres::Talk_Show;
    else if (str == "thriller")
        return Genres::Thriller;
    else if (str == "war")
        return Genres::War;
    else if (str == "adult")
        return Genres::Adult;
    throw std::invalid_argument("Unknown genre: " + str);
}

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
static TitleType strToTitleType(const std::string &str)
{
    if (str == "movie")
        return TitleType::movie;
    else if (str == "shortFilm")
        return TitleType::shortFilm;
    else if (str == "tvSeries")
        return TitleType::tvSeries;
    else if (str == "tvEpisode")
        return TitleType::tvEpisode;
    else if (str == "tvMiniSeries")
        return TitleType::tvMiniSeries;
    else if (str == "video")
        return TitleType::video;
    else if (str == "videoGame")
        return TitleType::videoGame;
    else if (str == "tvMovie")
        return TitleType::tvMovie;
    else if (str == "tvSpecial")
        return TitleType::tvSpecial;
    else if (str == "tvShort")
        return TitleType::tvShort;
    throw std::runtime_error("Tipo de título desconhecido: " + str);
}

class Cinema;

class Filme
{
public:
    std::string tConst;
    std::string titleType;    // Mudar para enum TitleType
    std::string primaryGenre; // Mudar para enum Genres
    std::string primaryTitle;
    std::string originalTitle;
    bool isAdult;
    short startYear;
    short endYear;
    int runTimesMinutes;
    std::vector<std::string> genres;

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
            /// Adiciona cada gênero encontrado na std::vector
            genres.push_back(genero_individual);
        }

        // ---- Lógica para tratar o '\N' e converter para número ----
        // Se a string for "\\N", 0 sera o valor padrão, caso ao contraio o valor sera lido.
        // "\\N" em vez de "\N" no código pois a primeira '\' é um caractere de escape.

        isAdult = (isAdult_str == "\\N") ? 0 : std::stoi(isAdult_str);
        startYear = (startYear_str == "\\N") ? 0 : std::stoi(startYear_str);
        endYear = (endYear_str == "\\N") ? 0 : std::stoi(endYear_str);
        runTimesMinutes = (runtime_str == "\\N") ? 0 : std::stoi(runtime_str);
    }

    ~Filme() = default;
    void transformaString();

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

    std::vector<std::string> getGenres()
    {
        return genres;
    }

    void setGenres(const std::vector<std::string> &genres)
    {
        this->genres = genres;
    }
};
