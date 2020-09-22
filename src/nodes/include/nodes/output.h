#pragma once

#include <nodes/node.h>

class OutputNode : public Node {
public:
    bool isDefault = false;

    std::string list() const override;

    OutputNode(Parser &parser, Node *parent);
};