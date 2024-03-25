/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-03-23 17:38
 */

#pragma once

#include <string>

typedef enum symbolType
{
    Token_t,
    Nonterminal_t,
    PrecSymbol_t
} SymbolType;

class Symbol
{
protected:
    SymbolType symbType;

public:
    virtual ~Symbol()
    {
    }

    bool operator==(const Symbol& other) const;
    bool operator!=(const Symbol& other) const;

    SymbolType GetSymbolType() const;

    virtual std::string GetTypeString() const = 0;
    virtual Symbol* Clone() const = 0;
};