#pragma once

#include <nodes/node.h>

class MakeNode : public Node {
public:
    std::string list() const override;

    MakeNode(Parser &parser, Node *parent);
};