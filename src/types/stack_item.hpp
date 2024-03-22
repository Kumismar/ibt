/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include <string>

typedef enum symbolType
{
    Token_t,
    Nonterminal_t,
    PrecSymbol_t
} SymbolType;

class StackItem
{
protected:
    SymbolType symbType;

public:
    virtual ~StackItem()
    {
    }

    bool operator==(const StackItem& other) const;
    bool operator!=(const StackItem& other) const;

    SymbolType GetSymbolType() const;

    virtual std::string GetTypeString() const = 0;
    virtual StackItem* Clone() const = 0;
};