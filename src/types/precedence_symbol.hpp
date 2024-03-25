/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:38
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

class PrecedenceSymbol : public Symbol
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
    Symbol* Clone() const override;

    bool operator==(const PrecedenceType& type) const;
    bool operator==(const PrecedenceSymbol& other) const;
};