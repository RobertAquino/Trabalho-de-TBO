#pragma once

#include <string>
#include <vector>
#include "Parser.hpp"
#include "Filtro.hpp"
#include "FiltroGenero.hpp"
// #include "FiltroDuracao.hpp"
// #include "FiltroAno.hpp"
#include "FiltroTitleType.hpp"

class SistemaDeFiltro
{
private:
    Node *rootNode = nullptr;
    HashMap<Genres, std::vector<int>> baseFilmesGenres;
    HashMap<TitleType, std::vector<int>> baseFilmesTitleTypes;

public:
    SistemaDeFiltro(const std::string &expression, HashMap<Genres, std::vector<int>> &baseFilmesGenres, HashMap<TitleType, std::vector<int>> &baseFilmesTitleTypes)
        : baseFilmesGenres(baseFilmesGenres), baseFilmesTitleTypes(baseFilmesTitleTypes)
    {
        std::cout << "Construindo árvore de filtro a partir da expressão: " << expression << "\n";
        Tokenizer tokenizer(expression);
        auto tokens = tokenizer.tokenize();
        tokenizer.printTokens();
        Parser parser(tokens);
        rootNode = parser.parse();
        if (!rootNode)
        {
            throw std::runtime_error("Erro ao analisar a expressão de filtro.");
        }

        assosiateFilter(rootNode);
        std::cout << "Árvore de filtro construída com sucesso.\n";
        printNode(rootNode, 0);
    }

    ~SistemaDeFiltro()
    {
        deleteTree(rootNode);
    }

    // Avalia a expressão de filtro e retorna os filmes filtrados
    HashSet<int> filtrar(const HashSet<int> &base)
    {
        return avaliar(rootNode, base);
    }

    void print() const
    {
        printNode(rootNode, 0);
    }

private:
    // Recursivamente liga value → Filtro*
    void assosiateFilter(Node *node)
    {
        if (!node)
            return;
        if (node->type == NodeType::FILTER)
        {
            node->filter = construirFiltroAPartirDe(node->value);
        }
        assosiateFilter(node->left);
        assosiateFilter(node->right);
    }

    Filtro *construirFiltroAPartirDe(const std::string &raw)
    {
        if (raw.find("#g") == 0)
        {
            std::string args = raw.substr(2);
            // Ignore {}
            args = args.substr(1, args.size() - 2); // Remove { e }
            // Converte a string args para Genres
            // Exemplo: "#g{action}" → "action"
            Genres genre = strToGenre(args);
            return new FiltroGenero(genre, baseFilmesGenres);
        }
        else if (raw.find("#d") == 0)
        {
            // return new FiltroDuracao(...);
        }
        else if (raw.find("#a") == 0)
        {
            // return new FiltroAno(...);
        }
        else if (raw.find("#t") == 0)
        {
            std::string args = raw.substr(2);
            args = args.substr(1, args.size() - 2); // Remove { e }
            TitleType titleType = strToTitleType(args);
            return new FiltroTitleType(titleType, baseFilmesTitleTypes);
        }
        return nullptr;
    }

    HashSet<int> avaliar(Node *node, const HashSet<int> &base)
    {
        if (!node)
            return {};

        if (node->type == NodeType::FILTER)
        {
            return node->filter->aplicar();
        }

        if (node->op == '!')
        {
            auto sub = avaliar(node->right, base);
            return subtrair(base, sub);
        }

        auto esq = avaliar(node->left, base);
        auto dir = avaliar(node->right, base);

        if (node->op == '&')
        {
            return interseccao(esq, dir);
        }
        else if (node->op == '|')
        {
            return uniao(esq, dir);
        }

        return {};
    }

    HashSet<int> interseccao(const HashSet<int> &a, const HashSet<int> &b)
    {
        HashSet<int> resultado;
        for (int i = 0; i < a.getSize(); ++i)
        {
            std::vector<int> itens = a.getAll();
            for (const auto &item : itens)
            {
                if (b.contains(item))
                {
                    resultado.put(item);
                }
            }
        }
        return resultado;
    }

    HashSet<int> uniao(const HashSet<int> &a, const HashSet<int> &b)
    {
        HashSet<int> resultado = a;
        for (int i = 0; i < b.getSize(); ++i)
        {
            std::vector<int> itens = b.getAll();
            for (const auto &item : itens)
            {
                if (!resultado.contains(item))
                {
                    resultado.put(item);
                }
            }
        }
        return resultado;
    }

    HashSet<int> subtrair(const HashSet<int> &total, const HashSet<int> &sub)
    {
        HashSet<int> resultado;
        for (int i = 0; i < total.getSize(); ++i)
        {
            std::vector<int> itens = total.getAll();
            for (const auto &item : itens)
            {
                if (!sub.contains(item))
                {
                    resultado.put(item);
                }
            }
        }
        return resultado;
    }

    void deleteTree(Node *node)
    {
        if (!node)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node->filter;
        delete node;
    }

    void printNode(Node *node, int depth) const
    {
        if (!node)
            std::cout << "Nó nulo\n";
        return;
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";

        if (node->type == NodeType::FILTER)
            std::cout << "Filtro: " << node->value << "\n";
        else
            std::cout << "Op: " << node->op << "\n";

        printNode(node->left, depth + 1);
        printNode(node->right, depth + 1);
    }
};
