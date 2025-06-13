#pragma once

#include "cinema.hpp"
#include <iostream>

enum class Genres
{
    Action = 0, Adventure = 1, Animation = 2,
    Biography = 3, Comedy = 4, Crime = 5,
    Documentary = 6, Drama = 7, Family = 8,
    Fantansy = 9, Game_Show = 10, History = 11,
    Horror = 12, Music = 13, Music = 14,
    Musicial = 15, Mystery = 16, News = 17,
    Reality_Tv = 18, Romance = 19, Sci_fi = 20,
    Short = 21, Sport = 22, Talk_Show = 23,
    Thriller = 24, War = 25, Adult = 26
};

class Filme{
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
    std::string genre;

    Filme();
    ~Filme();

    std::string getTitleType()
    {
        return titleType;
    }
    Cinema getCinema()
    {
        return cinema;
    }
    std::string getGenres()
    {
        return genre;
    }
};