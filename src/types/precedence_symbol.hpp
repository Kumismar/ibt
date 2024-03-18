/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

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
    PrecedenceSymbol(const PrecedenceType type);
    PrecedenceSymbol(const PrecedenceSymbol& old);

    ~PrecedenceSymbol() override
    {
    }

    PrecedenceType GetPrecedenceType() const;
    std::string GetTypeString() const override;
    StackItem* Clone() const override;

    bool operator==(const PrecedenceType& type) const;
    bool operator==(const PrecedenceSymbol& other) const;
};