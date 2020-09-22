#include <nodes/if.h>

#include <nodes/constexpr.h>
#include <nodes/code.h>

#include <fmt/format.h>

std::string IfNode::list() const {
    return "IfNode";
}

IfNode::IfNode(Parser &parser, Node *parent) : Node(Type::If, parent) {
    while (!parser.reachedEnd()) {
        if (parser.peekWord() == "if") {
            parser.nextWord();
            children.push_back(ConstexprNode::eval(parser, this));
        } else {
            hasDefaultBranch = true;
        }

        if (parser.nextWord() != "{")
            throw std::runtime_error(fmt::format("Expected {{ but got {}.", parser.lastWord()));

        numOfBranches++;
        children.push_back(std::make_shared<CodeNode>(parser, this));
        if (parser.nextWord() != "}")
            throw std::runtime_error(fmt::format("Expected }} but got {}.", parser.lastWord()));

        if (parser.peekWord() != "else") {
            break;
        } else {
            if (hasDefaultBranch)
                throw std::runtime_error("Unexpected double else statement.");

            parser.nextWord();
        }
    }
}