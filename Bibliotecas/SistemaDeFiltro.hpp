#pragma once

#include <string>
#include <vector>
#include "Parser.hpp"
#include "Filtro.hpp"
#include "FiltroGenero.hpp"
#include "FiltroLocation.hpp"
#include "YearFilter.hpp"
#include "DurationFilter.hpp"
#include "FiltroTitleType.hpp"
#include "PriceFilter.hpp"
#include "Cinema.hpp"
// #include "FiltroLocation.hpp"

class SistemaDeFiltro
{
private:
    Node *rootNode = nullptr;
    HashMap<Genres, std::vector<int>> baseFilmesGenres;
    HashMap<TitleType, std::vector<int>> baseFilmesTitleTypes;
    IntervalTreeYear *baseFilmesYear;
    IntervalTreeDuration *baseFilmesDuration;
    IntervalTreePrice *baseCinemasPrice;
    KDTree *baseCinemasLocation;
    bool isCinema = false;

    const std::vector<Filme> *filmesRef;
    const std::vector<Cinema> *cinemasRef;

public:
    SistemaDeFiltro(const std::string &expression, bool isCinema,
                    std::vector<Filme> *filmesRef, std::vector<Cinema> *cinemasRef,
                    KDTree *baseCinemasLocation, IntervalTreePrice *baseCinemasPrice,
                    IntervalTreeYear *baseFilmesYear, IntervalTreeDuration *baseFilmesDuration,
                    HashMap<Genres, std::vector<int>> &baseFilmesGenres,
                    HashMap<TitleType, std::vector<int>> &baseFilmesTitleTypes)
        : isCinema(isCinema), baseFilmesGenres(baseFilmesGenres), baseCinemasLocation(baseCinemasLocation), baseFilmesTitleTypes(baseFilmesTitleTypes), baseFilmesYear(baseFilmesYear), baseCinemasPrice(baseCinemasPrice), baseFilmesDuration(baseFilmesDuration), filmesRef(filmesRef), cinemasRef(cinemasRef)
    {
        Tokenizer tokenizer(expression);
        auto tokens = tokenizer.tokenize();
        tokenizer.printTokens();
        Parser parser(tokens);
        rootNode = parser.parse();
        if (!rootNode)
        {
            throw std::runtime_error("Erro ao analisar a expressao de filtro.");
        }

        if (rootNode->type != NodeType::OPERATOR)
        {
            std::cout << "Raiz da arvore nao eh um operador, mas um filtro: " << rootNode->value << "\n";
        }
        else
        {
            std::cout << "Raiz da arvore eh um operador: " << rootNode->op << "\n";
        }
        associateFilter(rootNode);

        if (rootNode->type == NodeType::OPERATOR)
        {
            std::cout << "Tipo da raiz: Operador (" << rootNode->op << ")\n";
        }
        else if (rootNode->type == NodeType::FILTER)
        {
            std::cout << "Tipo da raiz: Filtro (" << rootNode->value << ")\n";
        }
        printNode(rootNode, 0);
    }

    ~SistemaDeFiltro()
    {
        deleteTree(rootNode);
    }

    // Avalia a expressão de filtro e retorna os filmes filtrados
    HashSet<int> filtrar(const HashSet<int> &baseFilmes, const HashSet<int> &baseCinema)
    {
        if (!rootNode)
        {
            std::cerr << "Erro: raiz da árvore de filtro não está definida.\n";
            throw std::runtime_error("Árvore de filtro não inicializada.");
        }
        std::cout << "Iniciando avaliação da árvore de filtro...\n";
        if (baseFilmes.getSize() == 0)
        {
            std::cerr << "Erro: baseFilmes de filmes está vazia.\n";
            throw std::runtime_error("Base de filmes vazia.");
        }
        std::cout << "Base de filmes contem " << baseFilmes.getSize() << " itens.\n";
        std::cout << "Avaliacao da arvore de filtro iniciada.\n";
        if (isCinema)
        {
            HashSet<int> resultado = avaliar(rootNode, baseFilmes, baseCinema);
            if (!(rootNode->isCinema))
            {
                return cinemaTransform(resultado);
            }
            return resultado;
        }
        return avaliar(rootNode, baseFilmes, baseCinema);
    }

    void print() const
    {
        printNode(rootNode, 0);
    }

private:
    // Recursivamente liga value → Filtro*
    void associateFilter(Node *node)
    {
        if (!node)
            return;
        if (node->type == NodeType::FILTER)
        {
            std::cout << "Associando filtro: " << node->value << "\n";
            node->filter = construirFiltroAPartirDe(node->value);
            if (!node->filter)
            {
                std::cerr << "Erro ao construir filtro a partir de: " << node->value << "\n";
                throw std::runtime_error("Filtro inválido: " + node->value);
            }
            if (dynamic_cast<FiltroLocation *>(node->filter) || dynamic_cast<FiltroPreco *>(node->filter))
            {
                node->isCinema = true;
            }
            std::cout << "Filtro associado com sucesso: " << node->value << "\n";
        }
        associateFilter(node->left);
        associateFilter(node->right);
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
            std::cout << "Construindo filtro de genero a partir de: " << args << "\n";
            Genres genre = strToGenre(args);
            std::cout << "Gênero convertido: " << static_cast<int>(genre) << "\n";
            return new FiltroGenero(genre, baseFilmesGenres);
        }
        else if (raw.find("#d") == 0)
        {
            std::string args = raw.substr(2);
            args = args.substr(1, args.size() - 2);
            std::cout << "Construindo filtro de duracao a partir de" << args << '\n';
            int virgula = args.find(',');

            int minDuration = std::stoi(args.substr(0, virgula));
            int maxDuration = std::stoi(args.substr(virgula + 1));

            return new FiltroDuration(baseFilmesDuration->root, maxDuration, minDuration);
        }
        else if (raw.find("#a") == 0)
        {
            std::string args = raw.substr(2);
            args = args.substr(1, args.size() - 2);
            std::cout << "Construindo filtro de ano a partir de: " << args << '\n';
            int virgula = args.find(',');

            int minYear = std::stoi(args.substr(0, virgula));
            int maxYear = std::stoi(args.substr(virgula + 1));

            return new FiltroAno(baseFilmesYear->root, maxYear, minYear);
        }
        else if (raw.find("#t") == 0)
        {
            std::string args = raw.substr(2);
            args = args.substr(1, args.size() - 2); // Remove { e }
            TitleType titleType = strToTitleType(args);
            return new FiltroTitleType(titleType, baseFilmesTitleTypes);
        }
        else if (raw.find("#p") == 0)
        {
            std::string args = raw.substr(2);
            args = args.substr(1, args.size() - 2); // Remove { e }
            double precoMax = std::stod(args);
            return new FiltroPreco(baseCinemasPrice->root, precoMax);
        }
        else if (raw.find("#l") == 0)
        {
            std::string args = raw.substr(2);
            args = args.substr(1, args.size() - 2); // Remove { e }
            int primeira = args.find(',');
            int segunda = args.find(',', primeira + 1);

            int x = std::stoi(args.substr(0, primeira));
            int y = std::stoi(args.substr(primeira + 1, segunda - primeira - 1));
            int r = std::stoi(args.substr(segunda + 1));

            return new FiltroLocation(baseCinemasLocation, x, y, r);
        }
        return nullptr;
    }

    HashSet<int> avaliar(Node *node, const HashSet<int> &baseFilmes, const HashSet<int> &baseCinemas)
    {
        if (!node)
            return {};

        if (node->type == NodeType::FILTER)
        {
            std::cout << "Aplicando filtro: " << node->value << "\n";
            return node->filter->aplicar();
        }

        if (node->op == '!')
        {
            auto sub = avaliar(node->right, baseFilmes, baseCinemas);

            return subtrair(dynamic_cast<FiltroLocation *>(node->filter) ||
                                    dynamic_cast<FiltroPreco *>(node->filter)
                                ? baseCinemas
                                : baseFilmes,
                            sub);
        }

        auto esq = avaliar(node->left, baseFilmes, baseCinemas);
        auto dir = avaliar(node->right, baseFilmes, baseCinemas);

        if (node->left->isCinema && !(node->right->isCinema))
        {
            dir = cinemaTransform(dir);
            node->right->isCinema = true;
        }
        else if (!(node->left->isCinema) && node->right->isCinema)
        {
            esq = cinemaTransform(esq);
            node->left->isCinema = true;
        }

        if (node->op == '&')
        {
            std::cout << "Aplicando interseção...\n";
            if (esq.getSize() == 0 || dir.getSize() == 0)
            {
                std::cout << "Uma das partes da interseção está vazia, retornando vazia.\n";
                return {};
            }
            std::cout << "Interseção entre " << esq.getSize() << " e " << dir.getSize() << " itens.\n";
            if (esq.getSize() == 0 && dir.getSize() == 0)
            {
                std::cout << "Ambas as partes estão vazias, retornando vazia.\n";
                return {};
            }
            return interseccao(esq, dir);
        }
        else if (node->op == '|')
        {
            return uniao(esq, dir);
        }

        return {};
    }

    HashSet<int> cinemaTransform(const HashSet<int> filmes)
    {
        HashSet<int> resultado;
        std::vector<int> filmesId = filmes.getAll();
        for (const auto &id : filmesId)
        {
            std::vector<int> cinemas = filmesRef->at(id).cinemasIds;
            for (const auto &cinema : cinemas)
            {
                resultado.put(cinema);
            }
        }
        return resultado;
    }

    HashSet<int> interseccao(const HashSet<int> &a, const HashSet<int> &b)
    {
        if (a.getSize() > b.getSize())
        {
            std::cout << "Interseção: A base A é maior que a base B, trocando as bases.\n";
            return interseccao(b, a);
        }
        HashSet<int> resultado;
        std::vector<int> itensA = a.getAll();
        for (const int &itemA : itensA)
        {
            if (b.contains(itemA))
            {
                resultado.put(itemA);
            }
        }
        std::cout << "Interseção resultou em " << resultado.getSize() << " itens.\n";
        return resultado;
    }

    HashSet<int> uniao(const HashSet<int> &a, const HashSet<int> &b)
    {
        HashSet<int> resultado = a;

        std::vector<int> elementosB = b.getAll();
        for (const int &item : elementosB)
        {
            if (!resultado.contains(item))
            {
                resultado.put(item);
            }
        }

        return resultado;
    }

    HashSet<int> subtrair(const HashSet<int> &total, const HashSet<int> &sub)
    {
        HashSet<int> resultado;
        std::vector<int> itensTotal = total.getAll();

        for (auto &item : itensTotal)
        {
            if (sub.contains(item))
            {
                continue;
            }

            resultado.put(item);
        }

        return resultado;
    }

    void deleteTree(Node *node)
    {
        if (!node)
            return;
        delete node;
    }

    void printNode(Node *node, int depth) const
    {
        if (!node)
        {
            return;
        }
        for (int i = 0; i < depth; ++i)
            std::cout << "\t";

        if (node->type == NodeType::FILTER)
            std::cout << "Filtro: " << node->value << "\n";
        else
            std::cout << "Op: " << node->op << "\n";

        printNode(node->left, depth + 1);
        printNode(node->right, depth + 1);
    }
};
