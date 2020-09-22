#include <nodes/constexpr.h>

#include <nodes/utils.h>
#include <nodes/operator.h>

#include <fmt/format.h>

std::vector<OperatorRule<ConstexprNode::ConstexprOpTypeUnary>> constexprUnaryRules = {
    { ConstexprNode::ConstexprOpTypeUnary::Not, { { "!" } } },
    { ConstexprNode::ConstexprOpTypeUnary::Minus, { { "-" } } },
    { ConstexprNode::ConstexprOpTypeUnary::NotBitwise, { { "~" } } },
};

std::vector<OperatorRule<ConstexprNode::ConstexprOpTypeBinary>> constexprBinaryRules = {
    { ConstexprNode::ConstexprOpTypeBinary::And, { { "&", "&" } } },
    { ConstexprNode::ConstexprOpTypeBinary::Or, { { "|", "|" } } },
    { ConstexprNode::ConstexprOpTypeBinary::LeftShift, { { "<", "<" } } },
    { ConstexprNode::ConstexprOpTypeBinary::RightShift, { { ">", ">" } } },
    { ConstexprNode::ConstexprOpTypeBinary::BitwiseAnd, { { "&" } } },
    { ConstexprNode::ConstexprOpTypeBinary::BitwiseOr, { { "|" } } },
    { ConstexprNode::ConstexprOpTypeBinary::BitwiseXor, { { "^" } } },
    { ConstexprNode::ConstexprOpTypeBinary::BitwiseNot, { { "~" } } },
    { ConstexprNode::ConstexprOpTypeBinary::Plus, { { "+" } } },
    { ConstexprNode::ConstexprOpTypeBinary::Minus, { { "-" } } },
    { ConstexprNode::ConstexprOpTypeBinary::Multitply, { { "*" } } },
    { ConstexprNode::ConstexprOpTypeBinary::Divide, { { "/" } } },
    { ConstexprNode::ConstexprOpTypeBinary::Equals, { { "=", "=" } } },
    { ConstexprNode::ConstexprOpTypeBinary::NotEquals, { { "!", "=" } } },
    { ConstexprNode::ConstexprOpTypeBinary::GreaterThanOrEqual, { { ">", "=" } } },
    { ConstexprNode::ConstexprOpTypeBinary::GreaterThan, { { ">" } } },
    { ConstexprNode::ConstexprOpTypeBinary::LesserThanOrEqual, { { "<", "=" } } },
    { ConstexprNode::ConstexprOpTypeBinary::LesserThan, { { "<" } } },
};

std::string ConstexprNode::unaryOpName(ConstexprOpTypeUnary op) {
    switch (op) {
        case ConstexprOpTypeUnary::Not: return "Not";
        case ConstexprOpTypeUnary::Minus: return "Minus";
        case ConstexprOpTypeUnary::NotBitwise: return "NotBitwise";
        default: return "Unknown";
    }
}

std::string ConstexprNode::binaryOpName(ConstexprOpTypeBinary op) {
    switch (op) {
        case ConstexprOpTypeBinary::And: return "And";
        case ConstexprOpTypeBinary::Or: return "Or";
        case ConstexprOpTypeBinary::LeftShift: return "LeftShift";
        case ConstexprOpTypeBinary::RightShift: return "RightShift";
        case ConstexprOpTypeBinary::BitwiseAnd: return "BitwiseAnd";
        case ConstexprOpTypeBinary::BitwiseOr: return "BitwiseOr";
        case ConstexprOpTypeBinary::BitwiseXor: return "BitwiseXor";
        case ConstexprOpTypeBinary::BitwiseNot: return "BitwiseNot";
        case ConstexprOpTypeBinary::Plus: return "Plus";
        case ConstexprOpTypeBinary::Minus: return "Minus";
        case ConstexprOpTypeBinary::Multitply: return "Multitply";
        case ConstexprOpTypeBinary::Divide: return "Divide";
        case ConstexprOpTypeBinary::Equals: return "Equals";
        case ConstexprOpTypeBinary::NotEquals: return "NotEquals";
        case ConstexprOpTypeBinary::GreaterThanOrEqual: return "GreaterThanOrEqual";
        case ConstexprOpTypeBinary::GreaterThan: return "GreaterThan";
        case ConstexprOpTypeBinary::LesserThanOrEqual: return "LesserThanOrEqual";
        case ConstexprOpTypeBinary::LesserThan: return "LesserThan";
        default: return "Unknown";
    }
}

std::shared_ptr<ConstexprNode> ConstexprNode::eval(Parser &parser, Node *parent) {
    return std::dynamic_pointer_cast<ConstexprNode>(
        parseOperator<ConstexprNode::ConstexprOpTypeUnary, ConstexprNode::ConstexprOpTypeBinary >(parser, parent,
            constexprUnaryRules, constexprBinaryRules,
            [](Parser &parser, Node *parent) {
                return std::make_shared<ConstexprNode>(parser, parent);
            },
            [](ConstexprNode::ConstexprOpTypeUnary type, Node *parent) {
                const auto &exp = std::make_shared<ConstexprNode>(parent);

                exp->unaryOp = type;

                return exp;
            },
            [](ConstexprNode::ConstexprOpTypeBinary type, Node *parent) {
                const auto &exp = std::make_shared<ConstexprNode>(parent);

                exp->binaryOp = type;

                return exp;
            }
        )
    );
}

bool ConstexprNode::isUnary() const {
    return unaryOp != ConstexprOpTypeUnary::Unknown;
}

bool ConstexprNode::isBinary() const {
    return binaryOp != ConstexprOpTypeBinary::Unknown;
}

std::string ConstexprNode::list() const {
    switch (constexprType) {
        case ConstexprType::Variable:
            return fmt::format("ConstexprNode (reference: {})", content);
        case ConstexprType::Number:
            return fmt::format("ConstexprNode (number: {})", content);
        case ConstexprType::Comparator:
            if (isUnary())
                return fmt::format("ConstexprNode (unary: {})", unaryOpName(unaryOp));
            if (isBinary())
                return fmt::format("ConstexprNode (binary: {})", binaryOpName(binaryOp));
        default:
            return "ConstexprNode (unknown)";
    }
}

ConstexprNode::ConstexprNode(Node *parent) : Node(Type::Constexpr, parent), constexprType(ConstexprType::Comparator) { }

ConstexprNode::ConstexprNode(Parser &parser, Node *parent) : Node(Type::Constexpr, parent) {
    if (isDigit(parser.peekWord(), true)) {
        constexprType = ConstexprType::Number;
        content = parseDigit(parser);
    } else {
        constexprType = ConstexprType::Variable;
        content = parser.nextWord();
    }
}