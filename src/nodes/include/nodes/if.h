#pragma once

#include <nodes/node.h>

class IfNode : public Node {
public:
    uint32_t numOfBranches = 0;
    bool hasDefaultBranch = false;

    std::string list() const override;

    IfNode(Parser &parser, Node *parent);
};