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
    bool isCinema = false;
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
        // std::cout << "Iniciando parse padrao\n";

        Node *expr = parseOr();
        expect(TokenType::END);
        printTree(expr);

        if (!expr)
        {
            std::cerr << "Erro: expressao vazia ou invalida.\n";
            return nullptr;
        }

        // std::cout << "Parse concluido. Retornando a raiz da arvore: " << expr->value << '\n';
        std::cout << "Tipo do nó raiz: " << (expr->type == NodeType::OPERATOR ? "Operador" : "Filtro") << '\n';
        if (expr->type == NodeType::OPERATOR)
        {
            std::cout << "Encontrado operador na raiz da arvore: " << expr->op << "\n";
        }
        else if (expr->type == NodeType::FILTER)
        {
            std::cout << "Encontrado filtro na raiz da arvore: " << expr->value << "\n";
        }
        else
        {
            std::cout << "Raiz da arvore nao eh um operador ou filtro.\n";
        }

        return expr;
    }

    void printTree(Node *node, int depth = 0)
    {
        if (!node)
        {
            return;
        }

        for (int i = 0; i < depth; ++i)
            std::cout << "  ";

        if (node->type == NodeType::OPERATOR)
        {
            std::cout << "Operator: " << node->op << "\n";
        }
        else if (node->type == NodeType::FILTER)
        {
            std::cout << "Filter: " << node->value << "\n";
        }
        else
        {
            std::cout << "Unknown node type\n";
        }

        printTree(node->left, depth + 1);
        printTree(node->right, depth + 1);
    }

private:
    Node *parseOr()
    {
        // std::cout << "Iniciando parseOr\n";
        //  parseOr -> parseAnd (| parseAnd)*
        Node *node = parseAnd();
        while (match(TokenType::OPERATOR, "|"))
        {
            Node *right = parseAnd();
            Node *orNode = new Node(NodeType::OPERATOR, '|');
            orNode->left = node;
            orNode->right = right;
            node = orNode;
        }

        // std::cout << "ParseOr concluido\n";
        if (node->type == NodeType::OPERATOR && node->op == '|')
        {
            std::cout << "Encontrado operador OR na raiz da arvore: " << node->value << "\n";
        }
        return node;
    }

    Node *parseAnd()
    {
        // std::cout << "Iniciando parseAnd\n";
        //  parseAnd -> parseUnary (& parseUnary)*
        Node *node = parseUnary();
        while (match(TokenType::OPERATOR, "&"))
        {
            Node *right = parseUnary();
            Node *andNode = new Node(NodeType::OPERATOR, '&');
            andNode->left = node;
            andNode->right = right;
            node = andNode;
        }

        // std::cout << "ParseAnd concluido\n";
        if (node->type == NodeType::OPERATOR && node->op == '&')
        {
            std::cout << "Encontrado operador AND na raiz da arvore: " << node->value << "\n";
        }
        return node;
    }

    Node *parseUnary()
    {
        // std::cout << "Iniciando parseUnary\n";
        if (match(TokenType::OPERATOR, "!"))
        {
            Node *operand = parseUnary();
            Node *notNode = new Node(NodeType::OPERATOR, '!');
            notNode->left = operand; // Mude de 'right' para 'left' para consistência
            return notNode;
        }
        // std::cout << "ParseUnary concluido\n";
        return parsePrimary();
    }
    Node *parsePrimary()
    {
        // std::cout << "Iniciando parsePrimary\n";
        // std::cout << "Pos atual: " << pos << "\n";
        // std::cout << "Tokens restantes: " << tokens.size() - pos << "\n";
        if (pos >= tokens.size())
        {
            throw std::runtime_error("Erro: fim dos tokens alcançado inesperadamente.");
        }

        std::cout << "Token atual: " << tokens[pos].value << "\n";
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
                std::cout << "Encontrado bloco de argumentos: " + filtroRaw + "\n";
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
        std::cout << "Bloco de argumentos parseado: " << result << "\n";
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
