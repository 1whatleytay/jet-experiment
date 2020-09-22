#pragma once

#include <nodes/node.h>

class RootNode : public Node {
public:
    std::string list() const override;

    RootNode(Parser &parser, Node *parent);
};