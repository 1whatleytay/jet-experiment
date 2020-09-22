#include <nodes/expression.h>

#include <nodes/operator.h>
#include <nodes/constexpr.h>

#include <fmt/format.h>

#include <queue>

std::vector<OperatorRule<ExpressionNode::ExpressionOpTypeUnary>> expressionUnaryRules = {
    { ExpressionNode::ExpressionOpTypeUnary::And, { { "and" }, { "&" } } },
    { ExpressionNode::ExpressionOpTypeUnary::Or, { { "or" }, { "|" } } },
    { ExpressionNode::ExpressionOpTypeUnary::Not, { { "not" }, { "!" } } },
};

std::vector<OperatorRule<ExpressionNode::ExpressionOpTypeBinary>> expressionBinaryRules = {
    { ExpressionNode::ExpressionOpTypeBinary::And, { { "and" }, { "&" } } },
    { ExpressionNode::ExpressionOpTypeBinary::Or, { { "or" }, { "|" } } },
    { ExpressionNode::ExpressionOpTypeBinary::Not, { { "not" }, { "!" } } },
    { ExpressionNode::ExpressionOpTypeBinary::Nor, { { "nor" }, { "!|" } } },
    { ExpressionNode::ExpressionOpTypeBinary::Nand, { { "nand" }, { "!&" } } },
};

std::string ExpressionNode::unaryOpName(ExpressionOpTypeUnary op) {
    switch (op) {
        case ExpressionOpTypeUnary::And: return "And";
        case ExpressionOpTypeUnary::Or: return "Or";
        case ExpressionOpTypeUnary::Not: return "Not";
        default: return "Unknown";
    }
}
std::string ExpressionNode::binaryOpName(ExpressionOpTypeBinary op) {
    switch (op) {
        case ExpressionOpTypeBinary::And: return "And";
        case ExpressionOpTypeBinary::Or: return "Or";
        case ExpressionOpTypeBinary::Not: return "Not";
        case ExpressionOpTypeBinary::Nor: return "Nor";
        case ExpressionOpTypeBinary::Nand: return "Nand";
        default: return "Unknown";
    }
}

std::shared_ptr<ExpressionNode> ExpressionNode::eval(Parser &parser, Node *parent) {
    return std::dynamic_pointer_cast<ExpressionNode>(
        parseOperator<ExpressionNode::ExpressionOpTypeUnary, ExpressionNode::ExpressionOpTypeBinary>(parser, parent,
            expressionUnaryRules, expressionBinaryRules,
            [](Parser &parser, Node *parent) {
                return std::make_shared<ExpressionNode>(parser, parent);
            },
            [](ExpressionNode::ExpressionOpTypeUnary type, Node *parent) {
                const auto &exp = std::make_shared<ExpressionNode>(parent);

                exp->unaryOp = type;

                return exp;
            },
            [](ExpressionNode::ExpressionOpTypeBinary type, Node *parent) {
                const auto &exp = std::make_shared<ExpressionNode>(parent);

                exp->binaryOp = type;

                return exp;
            }
        )
    );
}

bool ExpressionNode::isUnary() const {
    return unaryOp != ExpressionOpTypeUnary::Unknown;
}

bool ExpressionNode::isBinary() const {
    return binaryOp != ExpressionOpTypeBinary::Unknown;
}

std::string ExpressionNode::list() const {
    switch (expressionType) {
        case ExpressionType::Variable:
            if (extension.empty())
                return fmt::format(
                    "ExpressionNode (reference: {}, indexed: {})",
                    content, !children.empty());
            else
                return fmt::format(
                    "ExpressionNode (reference: {}, indexed: {}, extension: {})",
                    content, !children.empty(), extension);
        case ExpressionType::Literal:
            return fmt::format("ExpressionNode (literal: {})", content);
        case ExpressionType::Comparator:
            if (isUnary())
                return fmt::format("ExpressionNode (unary: {})", unaryOpName(unaryOp));
            if (isBinary())
                return fmt::format("ExpressionNode (binary: {})", binaryOpName(binaryOp));
        default:
            return "ExpressionNode (unknown)";
    }
}

ExpressionNode::ExpressionNode(Node *parent)
    : Node(Type::Expression, parent), expressionType(ExpressionType::Comparator) { }

ExpressionNode::ExpressionNode(Parser &parser, Node *parent) : Node(Type::Expression, parent) {
    std::string name = parser.nextWord();

    if (name.empty())
        throw std::runtime_error("Incomplete expression.");

    if (name == "$") {
        content = parser.nextWord();
        expressionType = ExpressionType::Literal;
    } else {
        content = name;
        expressionType = ExpressionType::Variable;

        if (parser.peekWord() == "[") {
            parser.nextWord(); // [
            children.push_back(ConstexprNode::eval(parser, this));
            if (parser.nextWord() != "]")
                throw std::runtime_error(fmt::format("Expected ] but got {}.", parser.lastWord()));
        }

        if (parser.peekWord() == ".") {
            parser.nextWord(); // .
            extension = parser.nextWord();
        }
    }
}