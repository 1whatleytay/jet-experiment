#pragma once

#include <nodes/node.h>

#include <map>
#include <vector>

class ChipNode : public Node {
public:
    std::string name;
    bool isMain = false;

    std::string list() const override;

    ChipNode(Parser &parser, Node *parent, Attributes attributes);
};