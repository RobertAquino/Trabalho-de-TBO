#pragma once

#include "ArrayList.hpp"
#include "Cinema.hpp"
#include <iostream>

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

class Filme
{
public:
    Cinema cinema;
    long tConst;
    std::string titleType;
    std::string primaryTitle;
    std::string originalTitle;
    bool isAdult;
    short startYear;
    short endYear;
    int runTimesMinutes;
    ArrayList<std::string> genres;

    Filme();
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

    long getTConst()
    {
        return tConst;
    }
    void setTConst(long tConst)
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
