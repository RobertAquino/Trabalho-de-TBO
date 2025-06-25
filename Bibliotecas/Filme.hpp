#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// Enumeração de todos os gêneros do arquivo
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
    Western = 25,
    Adult = 26
};

static void toLower(std::string &str)
{
    for (char &c : str)
    {
        c = static_cast<char>(std::tolower(c));
    }
}

static Genres strToGenre(const std::string &str)
{
    std::string newStr = str;
    toLower(newStr);
    if (newStr == "action")
        return Genres::Action;
    else if (newStr == "adventure")
        return Genres::Adventure;
    else if (newStr == "animation")
        return Genres::Animation;
    else if (newStr == "biography")
        return Genres::Biography;
    else if (newStr == "comedy")
        return Genres::Comedy;
    else if (newStr == "crime")
        return Genres::Crime;
    else if (newStr == "documentary")
        return Genres::Documentary;
    else if (newStr == "drama")
        return Genres::Drama;
    else if (newStr == "family")
        return Genres::Family;
    else if (newStr == "fantasy")
        return Genres::Fantansy;
    else if (newStr == "game-show")
        return Genres::Game_Show;
    else if (newStr == "history")
        return Genres::History;
    else if (newStr == "horror")
        return Genres::Horror;
    else if (newStr == "music")
        return Genres::Music;
    else if (newStr == "musical")
        return Genres::Musicial;
    else if (newStr == "mystery")
        return Genres::Mystery;
    else if (newStr == "news")
        return Genres::News;
    else if (newStr == "reality-tv")
        return Genres::Reality_Tv;
    else if (newStr == "romance")
        return Genres::Romance;
    else if (newStr == "sci-fi")
        return Genres::Sci_fi;
    else if (newStr == "short")
        return Genres::Short;
    else if (newStr == "sport")
        return Genres::Sport;
    else if (newStr == "talk-show")
        return Genres::Talk_Show;
    else if (newStr == "thriller")
        return Genres::Thriller;
    else if (newStr == "war")
        return Genres::War;
    else if (newStr == "western")
        return Genres::Western;
    else if (newStr == "adult")
        return Genres::Adult;
    throw std::invalid_argument("Unknown genre: " + newStr);
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
    std::string newStr = str;
    toLower(newStr);
    if (newStr == "movie")
        return TitleType::movie;
    else if (newStr == "short")
        return TitleType::shortFilm;
    else if (newStr == "tvseries")
        return TitleType::tvSeries;
    else if (newStr == "tvepisode")
        return TitleType::tvEpisode;
    else if (newStr == "tvminiseries")
        return TitleType::tvMiniSeries;
    else if (newStr == "video")
        return TitleType::video;
    else if (newStr == "videogame")
        return TitleType::videoGame;
    else if (newStr == "tvmovie")
        return TitleType::tvMovie;
    else if (newStr == "tvspecial")
        return TitleType::tvSpecial;
    else if (newStr == "tvshort")
        return TitleType::tvShort;
    throw std::invalid_argument("Tipo de título desconhecido: " + newStr);
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
    std::vector<Genres> genres;
    std::vector<int> cinemasIds = {};

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
            if (genero_individual == "\\N")
            {
                continue;
            }
            Genres genre = strToGenre(genero_individual);
            genres.push_back(genre);
        }

        // ---- Lógica para tratar o '\N' e converter para número ----
        // Se a string for "\\N", 0 sera o valor padrão, caso ao contraio o valor sera lido.
        // "\\N" em vez de "\N" no código pois a primeira '\' é um caractere de escape.

        // std::cout << "ID" + tconst_str << std::endl;
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

    std::string getTitleType() const
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

    std::vector<Genres> getGenres() const
    {
        return genres;
    }

    void setGenres(const std::vector<Genres> &genres)
    {
        this->genres = genres;
    }
};
