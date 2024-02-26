#pragma once

#include "stack_item.hpp"
#include <string>

typedef enum
{
    Push, // <
    Reduce, // >
    Equal, // =
    Invalid // x
} PrecedenceType;

class PrecedenceSymbol : public StackItem
{
private:
    PrecedenceType precType;

public:
    PrecedenceSymbol(PrecedenceType type);

    ~PrecedenceSymbol() override
    {
    }

    PrecedenceType GetPrecedenceType() const;
    std::string GetTypeString() const override;

    bool operator==(const PrecedenceType& type) const;
    bool operator==(const PrecedenceSymbol& other) const;
};