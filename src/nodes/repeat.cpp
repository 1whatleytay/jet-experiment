#include <nodes/repeat.h>

#include <nodes/code.h>
#include <nodes/declare.h>
#include <nodes/constexpr.h>

#include <fmt/format.h>

std::string RepeatNode::list() const {
    return "RepeatNode";
}

RepeatNode::RepeatNode(Parser &parser, Node *parent) : Node(Type::Repeat, parent) {
    if (parser.nextWord() != "repeat")
        throw std::runtime_error("Unknown internal error related to repeats.");

    children.push_back(ConstexprNode::eval(parser, this));

    if (parser.nextWord() != "as")
        throw std::runtime_error(fmt::format("Expected as in repeat statement but got {}.", parser.lastWord()));

    children.push_back(std::make_shared<DeclareNode>(parser, this));

    if (parser.nextWord() != "{")
        throw std::runtime_error(fmt::format("Expected {{ in repeat statement but got {}.", parser.lastWord()));

    children.push_back(std::make_shared<CodeNode>(parser, this));
    if (parser.nextWord() != "}")
        throw std::runtime_error(fmt::format("Expected }} but got {}.", parser.lastWord()));
}