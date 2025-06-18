#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

class Parse
{
public:
    std::string query;

    std::vector<std::string> createToken(std::string &query)
    {
        std::vector<std::string> token;
        std::string auxToken;
        std::stringstream ss(query);

        while (ss >> auxToken)
        {
            token.push_back(auxToken);
        }

        return token;
    }

    std::vector<std::string> organizeToken(std::vector<std::string> token)
    {
        std::vector<std::string> newToken;
        std::string aux;
        int index = 0;

        while (token.size() > index)
        {
            aux = token[index] + token[index + 1];
            newToken.push_back(aux);
            index += 2;
        }
        return newToken;
    }
};

// #t movie AND(#g Ação AND(#g AVENTURA)) OR (#d [90 120])

// query = #t movie AND #g{aventura, ACAO} OR #d[90 120] query = #t movie AND #g(AVENTURA, ACAO) OR #d[90 120]
/*
token[0] = #t movie;
token[1] = AND
token[2] = #g {AVENTURA, ACAP}
token[3] = OR
token[4] = #d[90 120];

token[0] = #t;
token[1] = movie
token[2] = AND
token[3] = #g
tokek[4] = #d[90 120];

n_token = 0;*/
