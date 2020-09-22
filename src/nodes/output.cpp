#include <nodes/output.h>

#include <nodes/expression.h>

#include <fmt/format.h>

std::string OutputNode::list() const {
    return "OutputNode";
}

OutputNode::OutputNode(Parser &parser, Node *parent) : Node(Type::Output, parent) {
    if (parser.nextWord() != "output")
        throw std::runtime_error(fmt::format("Expected output but got {}.", parser.lastWord()));

    if (parser.peekWord() == "default") {
        isDefault = true;
        parser.nextWord();
    }

    children.push_back(ExpressionNode::eval(parser, this));
}