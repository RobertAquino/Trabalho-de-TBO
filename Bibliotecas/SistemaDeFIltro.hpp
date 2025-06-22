#pragma once

#include <vector>
#include "Parser.hpp"

class SistemaDeFiltro
{
private:
    Parser parser;
    Tokenizer tokenizer;
    std::vector<Token> tokens;

public:
    SistemaDeFiltro(const std::string &expression) : tokenizer(expression), parser(tokenizer.tokenize())
    {
        tokens = parser.getTokens();
    }
};
