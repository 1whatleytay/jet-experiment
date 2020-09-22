#include <nodes/constant.h>

#include <fmt/format.h>

std::string ConstantNode::list() const {
    return fmt::format("ConstantNode ({})", name);
}

ConstantNode::ConstantNode(Parser &parser, Node *parent, bool define) : Node(Type::Constant, parent) {
    if (define) {
        if (parser.nextWord() != "const")
            throw std::runtime_error(fmt::format("Expected const but got {}.", parser.lastWord()));
    }

    name = parser.nextWord();

    if (parser.peekWord() == "=") {
        parser.nextWord();
        children.push_back(ConstexprNode::eval(parser, parent));
    }
}