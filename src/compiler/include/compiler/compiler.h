#pragma once

#include <string>

#include <nodes/node.h>

class Compiler {
    std::string source;

    static void list(const std::shared_ptr<Node> &node, uint32_t numTabs);
public:
    void compile();

    explicit Compiler(std::string source);
};
