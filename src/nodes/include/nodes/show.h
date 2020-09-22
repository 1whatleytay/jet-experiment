#pragma once

#include <nodes/node.h>

class ShowNode : public Node {
public:
    std::string list() const override;

    ShowNode(Parser &parser, Node *parent);
};