#pragma once

#include <nodes/node.h>

class CodeNode : public Node {
public:
    std::string list() const override;

    CodeNode(Parser &parser, Node *parent);
};