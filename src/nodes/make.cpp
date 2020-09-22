#include <nodes/make.h>

#include <nodes/declare.h>
#include <nodes/expression.h>

#include <fmt/format.h>

std::string MakeNode::list() const {
    return "MakeNode";
}

MakeNode::MakeNode(Parser &parser, Node *parent) : Node(Type::Make, parent) {
    if (parser.nextWord() != "make")
        throw std::runtime_error(fmt::format("Expected make but got {}.", parser.lastWord()));

    children.push_back(std::make_shared<DeclareNode>(parser, this));

    if (parser.peekWord() == "=") {
        parser.nextWord();

        if (children[0]->as<DeclareNode>()->chipType != typeWire)
            throw std::runtime_error("The = operator can only be used on wire types.");

        children.push_back(ExpressionNode::eval(parser, this));
    }
}