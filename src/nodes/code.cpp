#include <nodes/code.h>

#include <nodes/if.h>
#include <nodes/make.h>
#include <nodes/show.h>
#include <nodes/wire.h>
#include <nodes/output.h>
#include <nodes/repeat.h>
#include <nodes/constant.h>

std::string CodeNode::list() const {
    return "CodeNode";
}

CodeNode::CodeNode(Parser &parser, Node *parent) : Node(Type::Code, parent) {
    while (!parser.reachedEnd()) {
        std::string keyword = parser.peekWord();

        if (keyword == "}") {
            break;
        } else if (keyword == "make") {
            children.push_back(std::make_shared<MakeNode>(parser, this));
        } else if (keyword == "if") {
            children.push_back(std::make_shared<IfNode>(parser, this));
        } else if (keyword == "repeat") {
            children.push_back(std::make_shared<RepeatNode>(parser, this));
        } else if (keyword == "output") {
            children.push_back(std::make_shared<OutputNode>(parser, this));
        } else if (keyword == "show") {
            children.push_back(std::make_shared<ShowNode>(parser, this));
        } else if (keyword == "const") {
            children.push_back(std::make_shared<ConstantNode>(parser, this, true));
        } else {
            children.push_back(std::make_shared<WireNode>(parser, this));
        }
    }
}