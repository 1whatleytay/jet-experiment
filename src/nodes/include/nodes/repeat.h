#pragma once

#include <nodes/node.h>

class RepeatNode : public Node {
public:
    std::string list() const override;

    RepeatNode(Parser &parser, Node *parent);
};