#pragma once

// save me time
#include <parser/parser.h>

#include <string>
#include <vector>
#include <memory>
#include <functional>

typedef const std::vector<std::string> &Attributes;

class Node {
public:
    enum class Type {
        Root,
        Code,
        Chip,
        Statement,
        Expression,
        Declare,
        Make,
        Constant,
        Constexpr,
        Output,
        Show,
        If,
        Repeat,
        Wire,
    };

    Type type;
    Node *parent;
    std::vector<std::shared_ptr<Node>> children;

    virtual std::string list() const;

    Node *searchThis(const std::function<bool(Node *)> &checker);
    Node *searchParent(const std::function<bool(Node *)> &checker);

    template <typename T>
    inline T *as() { return dynamic_cast<T *>(this); }

    Node(Type type, Node *parent);
    virtual ~Node();
};
