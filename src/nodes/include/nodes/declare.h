#pragma once

#include <nodes/node.h>

#include <nodes/constexpr.h>

const std::string typeWire = "Wire";

class DeclareNode : public Node {
public:
    std::string name;
    std::string chipType = typeWire;

    bool isArray = false;
    uint32_t numConstants = 0;
    uint32_t numExpressions = 0;

    std::string list() const override;

    DeclareNode(Parser &parser, Node *parent);
};
