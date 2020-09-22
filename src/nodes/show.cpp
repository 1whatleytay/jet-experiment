#include <nodes/show.h>

#include <nodes/expression.h>

#include <fmt/format.h>

std::string ShowNode::list() const {
    return "ShowNode";
}

ShowNode::ShowNode(Parser &parser, Node *parent) : Node(Type::Show, parent) {
    if (parser.nextWord() != "show")
        throw std::runtime_error(fmt::format("Expected show but got {}.", parser.lastWord()));

    children.push_back(ExpressionNode::eval(parser, this));
}
