#pragma once

#include <nodes/node.h>

#include <nodes/constexpr.h>

#include <optional>

class ConstantNode : public Node {
public:
    std::string name;

    std::string list() const override;

    ConstantNode(Parser &parser, Node *parent, bool define = true);
};