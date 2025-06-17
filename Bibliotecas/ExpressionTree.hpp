#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include "Filtro.hpp"

enum class NodeType
{
    OPERATOR,
    FILTER
};

struct Node
{
    NodeType type;
    std::string value;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(NodeType t, const std::string &v) : type(t), value(v), left(nullptr), right(nullptr) {}
};

class ExpressionTree
{
private:
    Node *root;
    Node *parseExpression(const std::string &expression, size_t &pos);

    void deleteTree(Node *node);
    void skipWhitespace(const std::string &expression, size_t &pos);

public:
    ExpressionTree(const std::string &expression);
    ~ExpressionTree();

    void print(Node *node, int depth = 0) const;

    std::string toString(Node *node, int depth = 0) const;
};