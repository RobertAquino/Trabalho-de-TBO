#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include "Filtro.hpp"
#include "Tokenizer.hpp"

enum class NodeType
{
    OPERATOR,
    FILTER
};

struct Node
{
    NodeType type;
    char op = '\0'; // &, |, !
    Filtro *filter = nullptr;
    std::string value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(NodeType type, char op = '\0', Filtro *filter = nullptr, const std::string &value = "")
        : type(type), op(op), filter(filter), value(value), left(nullptr), right(nullptr) {}
    ~Node()
    {
        delete filter;
        delete left;
        delete right;
    }
};

class Parser
{
    std::vector<Token> tokens;
    size_t pos;

public:
    Parser(std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

    Node *parse()
    {
        Node *expr = parseOr();
        expect(TokenType::END);
        return expr;
    }

private:
    Node *parseOr()
    {
        Node *node = parseAnd();
        while (match(TokenType::OPERATOR, "|"))
        {
            Node *right = parseAnd();
            Node *orNode = new Node(NodeType::OPERATOR, '|');
            orNode->left = node;
            orNode->right = right;
            node = orNode;
        }
        return node;
    }

    Node *parseAnd()
    {
        Node *node = parseUnary();
        while (match(TokenType::OPERATOR, "&"))
        {
            Node *right = parseUnary();
            Node *andNode = new Node(NodeType::OPERATOR, '&');
            andNode->left = node;
            andNode->right = right;
            node = andNode;
        }
        return node;
    }

    Node *parseUnary()
    {
        if (match(TokenType::OPERATOR, "!"))
        {
            Node *operand = parseUnary();
            Node *notNode = new Node(NodeType::OPERATOR, '!');
            notNode->right = operand;
            return notNode;
        }
        return parsePrimary();
    }

    Node *parsePrimary()
    {
        if (match(TokenType::PAREN_OPEN))
        {
            Node *node = parseOr();
            expect(TokenType::PAREN_CLOSE);
            return node;
        }

        if (check(TokenType::LITERAL))
        {
            std::string filtroRaw = advance().value;

            // depois fazer { ... } ou [ ... ]
            std::string args;
            if (check(TokenType::SYMBOL, "{") || check(TokenType::SYMBOL, "["))
            {
                args = parseArgumentBlock();
                filtroRaw += args;
            }

            return new Node(NodeType::FILTER, '\0', nullptr, filtroRaw);
        }

        throw std::runtime_error("Erro: esperado filtro ou subexpressão.");
    }

    std::string parseArgumentBlock()
    {
        std::string result;
        Token start = advance(); // { ou [
        result += start.value;

        while (!check(TokenType::SYMBOL, start.value == "{" ? "}" : "]"))
        {
            result += advance().value;
        }

        result += advance().value; // fecha o bloco
        return result;
    }

    // utilitários
    bool match(TokenType type, const std::string &value = "")
    {
        if (check(type, value))
        {
            advance();
            return true;
        }
        return false;
    }

    bool check(TokenType type, const std::string &value = "")
    {
        if (pos >= tokens.size())
            return false;
        if (tokens[pos].type != type)
            return false;
        if (!value.empty() && tokens[pos].value != value)
            return false;
        return true;
    }

    Token advance()
    {
        if (pos < tokens.size())
            return tokens[pos++];
        return Token(TokenType::END, "");
    }

    void expect(TokenType type, const std::string &value = "")
    {
        if (!check(type, value))
        {
            throw std::runtime_error("Erro de sintaxe: esperado " + tokenTypeToStr(type) +
                                     (value.empty() ? "" : (" '" + value + "'")));
        }
        advance();
    }

    std::string tokenTypeToStr(TokenType type)
    {
        switch (type)
        {
        case TokenType::LITERAL:
            return "literal";
        case TokenType::SYMBOL:
            return "símbolo";
        case TokenType::OPERATOR:
            return "operador";
        case TokenType::PAREN_OPEN:
            return "'('";
        case TokenType::PAREN_CLOSE:
            return "')'";
        default:
            return "token";
        }
    }
};
