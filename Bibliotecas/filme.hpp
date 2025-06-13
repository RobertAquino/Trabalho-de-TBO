#pragma once

#include "cinema.hpp"
#include <iostream>

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
    std::string genres[];

    Filme();
    ~Filme();


};