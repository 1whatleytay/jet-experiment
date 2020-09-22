#include <nodes/chip.h>

#include <nodes/declare.h>
#include <nodes/constant.h>
#include <nodes/code.h>

#include <fmt/format.h>

std::string ChipNode::list() const {
    return fmt::format("ChipNode ({}{})", name, isMain ? "[main]" : "");
}

ChipNode::ChipNode(Parser &parser, Node *parent, Attributes attributes) : Node(Type::Chip, parent) {
    if (parser.nextWord() != "chip")
        throw std::runtime_error(fmt::format("Unexpected {}, expected chip.", parser.lastWord()));

    isMain = std::find(attributes.begin(), attributes.end(), "main") != attributes.end();

    std::string start = parser.nextWord();
    if (start != "{") {
        name = start;
        start = parser.nextWord();
    }

    // constants
    if (start == "[") {
        while (!parser.reachedEnd()) {
            if (parser.peekWord() == "]")
                break;

            children.push_back(std::make_shared<ConstantNode>(parser, this, false));

            if (parser.peekWord() == ",")
                parser.nextWord();
            else if (parser.peekWord() != "]")
                throw std::runtime_error("Unexpected symbol in between arguments.");
        }

        parser.nextWord(); // ]

        start = parser.nextWord();
    }

    // inputs
    if (start == "(") {
        while (!parser.reachedEnd() && parser.peekWord() != ")") {
            if (parser.peekWord() == ")")
                break;

            children.push_back(std::make_shared<DeclareNode>(parser, this));

            std::string next = parser.nextWord();

            if (next == ",")
                continue;

            if (next == ")")
                break;
        }

        if (parser.peekWord() == ")")
            throw std::runtime_error(fmt::format("Expected ] to close chip constants but got {}.", parser.lastWord()));

        start = parser.nextWord();
    }

    if (start != "{")
        throw std::runtime_error(fmt::format("Unexpected {}, expected {{ for chip.", start));

    children.push_back(std::make_shared<CodeNode>(parser, this));
    if (parser.nextWord() != "}")
        throw std::runtime_error(fmt::format("Expected }} but got {}.", parser.lastWord()));
}