#include "../Bibliotecas/ExpressionTree.hpp"

ExpressionTree::ExpressionTree(const std::string &expression)
{
    size_t pos = 0;
    root = parseExpression(expression, pos);
}

ExpressionTree::~ExpressionTree()
{
    deleteTree(root);
}

void ExpressionTree::deleteTree(Node *node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void ExpressionTree::skipWhitespace(const std::string &expression, size_t &pos)
{
    while (pos < expression.size() && std::isspace(expression[pos]))
    {
        pos++;
    }
}

Node *ExpressionTree::parseExpression(const std::string &expression, size_t &pos)
{
    skipWhitespace(expression, pos);

    if (pos >= expression.size())
    {
        return nullptr;
    }

    if (expression[pos] == '(')
    {
        pos++; // Pula '('
        Node *left = parseExpression(expression, pos);
        skipWhitespace(expression, pos);
        if (pos >= expression.size() || expression[pos] != ')')
        {
            throw std::runtime_error("Error: Expected ')'");
        }
        pos++; // Pula ')'
        return left;
    }

    if (std::isalpha(expression[pos]) || std::isdigit(expression[pos]))
    {
        size_t start = pos;
        while (pos < expression.size() && (std::isalpha(expression[pos]) || std::isdigit(expression[pos])))
        {
            pos++;
        }
        std::string value = expression.substr(start, pos - start);
        return new Node(NodeType::FILTER, value);
    }

    return nullptr;
}

void ExpressionTree::print(Node *node, int depth) const
{
    if (node)
    {
        print(node->right, depth + 1);
        std::cout << std::string(depth * 4, ' ') << node->value << std::endl;
        print(node->left, depth + 1);
    }
}

std::string ExpressionTree::toString(Node *node, int depth) const
{
    if (!node)
    {
        return "";
    }
    std::string result = toString(node->right, depth + 1);
    result += std::string(depth * 4, ' ') + node->value + "\n";
    result += toString(node->left, depth + 1);
    return result;
}