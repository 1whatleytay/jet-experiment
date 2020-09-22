#include <compiler/compiler.h>

#include <nodes/root.h>

#include <model/model.h>

#include <fmt/printf.h>

void Compiler::list(const std::shared_ptr<Node> &node, uint32_t numTabs) {
    fmt::print("{}{}\n", std::string(numTabs, '\t'), node->list());

    for (const std::shared_ptr<Node> &child : node->children) {
        list(child, numTabs + 1);
    }
}

void Compiler::compile() {
    Parser parser(source);

    std::shared_ptr<Node> root = std::make_shared<RootNode>(parser, nullptr);
    list(root, 0);

    Model model;

//    try {
//    } catch (const std::runtime_error &error) {
//        fmt::print("Error: {}.", error.what());
//    }
}

Compiler::Compiler(std::string source) : source(std::move(source)) { }
