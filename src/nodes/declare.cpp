#include <nodes/declare.h>

#include <nodes/expression.h>

#include <fmt/format.h>

std::string DeclareNode::list() const {
    return fmt::format("DeclareNode ({}, type: {}, array: {})", name, chipType, isArray);
}

DeclareNode::DeclareNode(Parser &parser, Node *parent) : Node(Type::Declare, parent) {
    name = parser.nextWord();

    if (parser.peekWord() == "[") { // declare as array
        parser.nextWord(); // skip [
        isArray = true;
        children.push_back(ConstexprNode::eval(parser, this));

        if (parser.nextWord() != "]")
            throw std::runtime_error(fmt::format("Expected ] to close array size, but got {}.", parser.lastWord()));
    }

    if (parser.peekWord() == ":") { // declare as type
        parser.nextWord(); // skip :

        chipType = parser.nextWord();

        if (parser.peekWord() == "[") { // declare constants
            parser.nextWord();

            while (!parser.reachedEnd()) {
                if (parser.peekWord() == "]")
                    break;

                numConstants++;
                children.push_back(ConstexprNode::eval(parser, this));

                if (parser.peekWord() == ",")
                    parser.nextWord();
                else if (parser.peekWord() != "]")
                    throw std::runtime_error(fmt::format("Unknown constant operator {}.", parser.lastWord()));
            }

            parser.nextWord(); // ]
        }

        if (parser.peekWord() == "(") {
            parser.nextWord();

            if (chipType == typeWire)
                throw std::runtime_error(fmt::format("Use = to connect wires."));

            while (!parser.reachedEnd()) {
                if (parser.peekWord() == ")")
                    break;

                numExpressions++;
                children.push_back(ExpressionNode::eval(parser, this));

                if (parser.peekWord() == ",")
                    parser.nextWord();
                else if (parser.peekWord() != ")")
                    throw std::runtime_error(fmt::format("Unknown constant operator {}.", parser.lastWord()));
            }

            parser.nextWord(); // )
        }
    }
}