#pragma once

#include <nodes/node.h>

class ExpressionNode : public Node {
public:
    enum class ExpressionType {
        Variable,
        Literal,
        Comparator
    };

    enum class ExpressionOpTypeUnary {
        And,
        Or,
        Not,
        Unknown,
    };

    enum class ExpressionOpTypeBinary {
        And,
        Or,
        Not,
        Nor,
        Nand,
        Unknown,
    };
    ExpressionType expressionType = ExpressionType::Variable;

    ExpressionOpTypeUnary unaryOp = ExpressionOpTypeUnary::Unknown;
    ExpressionOpTypeBinary binaryOp = ExpressionOpTypeBinary::Unknown;

    static std::string unaryOpName(ExpressionOpTypeUnary op);
    static std::string binaryOpName(ExpressionOpTypeBinary op);

    std::string content;
    std::string extension;

    bool isUnary() const;
    bool isBinary() const;

    static std::shared_ptr<ExpressionNode> eval(Parser &parser, Node *parent);

    std::string list() const override;

    explicit ExpressionNode(Node *parent);
    ExpressionNode(Parser &parser, Node *parent);
};