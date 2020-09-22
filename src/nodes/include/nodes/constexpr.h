#pragma once

#include <nodes/node.h>

class ConstexprNode : public Node {
public:
    enum class ConstexprType {
        Variable,
        Number,
        Comparator,
        Unknown,
    };

    enum class ConstexprOpTypeUnary {
        Not,
        Minus,
        NotBitwise,
        Unknown,
    };

    enum class ConstexprOpTypeBinary {
        And,
        Or,
        LeftShift,
        RightShift,
        BitwiseAnd,
        BitwiseOr,
        BitwiseXor,
        BitwiseNot,
        Plus,
        Minus,
        Multitply,
        Divide,
        Equals,
        NotEquals,
        GreaterThanOrEqual,
        GreaterThan,
        LesserThanOrEqual,
        LesserThan,
        Unknown,
    };

    static std::string unaryOpName(ConstexprOpTypeUnary op);
    static std::string binaryOpName(ConstexprOpTypeBinary op);

    ConstexprType constexprType = ConstexprType::Unknown;
    std::string content;

    ConstexprOpTypeUnary unaryOp = ConstexprOpTypeUnary::Unknown;
    ConstexprOpTypeBinary binaryOp = ConstexprOpTypeBinary::Unknown;

    bool isUnary() const;
    bool isBinary() const;

    static std::shared_ptr<ConstexprNode> eval(Parser &parser, Node *parent);

    std::string list() const override;

    ConstexprNode(Node *parent);
    ConstexprNode(Parser &parser, Node *parent);
};
