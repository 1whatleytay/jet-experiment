#pragma once

#include <nodes/node.h>

class ExpressionNode;

class WireNode : public Node {
public:
    ExpressionNode *getDestination();
    ExpressionNode *getSource();

    std::string list() const override;

    WireNode(Parser &parser, Node *parent);
};