#pragma once

#include <map>
#include <vector>

class Entity {
public:
    enum class Type {
        Buffer,
        And,
        Or,
        Not,
        Nor,
        Nand,
        Xor,
        Nxor,
        Unknown,
    };

    Type type = Type::Unknown;

    std::vector<size_t> inputs;
    std::vector<size_t> outputs;
};

class Model {
    std::map<void *, size_t> references;

public:
    std::vector<Entity> entities;

    size_t getOrCreate(void *reference);
};
