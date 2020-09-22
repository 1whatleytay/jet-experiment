#include <nodes/root.h>

#include <nodes/chip.h>

#include <fmt/format.h>

const char *attributeKeywords[] = {
    "main"
};

std::string RootNode::list() const {
    return "RootNode";
}

RootNode::RootNode(Parser &parser, Node *parent) : Node(Type::Root, parent) {
    while (!parser.reachedEnd()) {
        std::vector<std::string> attributes;

        std::string keyword = parser.peekWord();
        while (std::find(std::begin(attributeKeywords), std::end(attributeKeywords), keyword)
            != std::end(attributeKeywords)) {
            attributes.push_back(keyword);
            parser.nextWord();
            keyword = parser.peekWord();
        }

        if (keyword == "chip") {
            children.push_back(std::make_shared<ChipNode>(parser, this, attributes));
        } else { // keyword no match
            throw std::runtime_error(fmt::format("Unknown keyword {} in global scope.", keyword));
        }
    }
}