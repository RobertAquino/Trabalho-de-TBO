#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

enum class TokenType
{
    IDENTIFIER,  // ex: #g, #d
    SYMBOL,      // '{', '}', '[', ']', ',', ':'
    LITERAL,     // Ação, Terror, 100, etc.
    OPERATOR,    // &, |, !
    PAREN_OPEN,  // (
    PAREN_CLOSE, // )
    END          // fim da string
};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string &value) : type(type), value(value) {}
};

class Tokenizer
{
    std::string input;
    size_t pos;

public:
    Tokenizer(const std::string &s) : input(s), pos(0) {}

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;

        while (pos < input.size())
        {
            char c = input[pos];

            if (std::isspace(c))
            {
                ++pos;
            }
            else if (std::isalpha(c) || c == '#' || std::isdigit(c))
            {
                tokens.push_back(Token(TokenType::LITERAL, parseLiteral()));
            }
            else if (c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ':')
            {
                tokens.push_back(Token(TokenType::SYMBOL, std::string(1, c)));
                ++pos;
            }
            else if (c == '&' || c == '|' || c == '!')
            {
                tokens.push_back(Token(TokenType::OPERATOR, std::string(1, c)));
                ++pos;
            }
            else if (c == '(')
            {
                tokens.push_back(Token(TokenType::PAREN_OPEN, "("));
                ++pos;
            }
            else if (c == ')')
            {
                tokens.push_back(Token(TokenType::PAREN_CLOSE, ")"));
                ++pos;
            }
            else
            {
                throw std::runtime_error("Caractere inválido no input: " + std::string(1, c));
            }
        }

        tokens.push_back(Token(TokenType::END, ""));
        return tokens;
    }

private:
    std::string parseLiteral()
    {
        size_t start = pos;
        while (pos < input.size() &&
               (std::isalnum(input[pos]) || input[pos] == '#' || input[pos] == '_'))
            ++pos;
        return input.substr(start, pos - start);
    }
};
