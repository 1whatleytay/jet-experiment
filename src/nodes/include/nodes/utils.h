#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>

class Node;
class Parser;
class ExpressionNode;

class QuotesInsertPoint {
public:
    uint32_t insertPoint;
    std::shared_ptr<ExpressionNode> expressionNode;
};

class QuotesValue {
public:
    std::string text;
    std::vector<QuotesInsertPoint> inserts;
};

QuotesValue parseString(Node *parent, Parser &parser, const std::string &quote = "\'");

std::string parseDigit(Parser &parser);
bool isDigit(const std::string &value, bool decimal = false);
