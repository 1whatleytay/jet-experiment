#include <nodes/wire.h>

#include <nodes/expression.h>

#include <fmt/format.h>

ExpressionNode *WireNode::getDestination() { return children[0]->as<ExpressionNode>(); }
ExpressionNode *WireNode::getSource() { return children[1]->as<ExpressionNode>(); }

std::string WireNode::list() const {
    return "WireNode";
}

WireNode::WireNode(Parser &parser, Node *parent) : Node(Type::Wire, parent) {
    // children[0] destination
    children.push_back(ExpressionNode::eval(parser, this));

    if (parser.nextWord() != "=")
        throw std::runtime_error(fmt::format("Expected = for wiring statement but got {}.", parser.lastWord()));

    // children[1] source
    children.push_back(ExpressionNode::eval(parser, this));
}