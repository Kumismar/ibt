#pragma once

#include "nonterminal.hpp"
#include "table_index.hpp"
#include "token.hpp"
#include <vector>

class LLRowAccessor
{
private:
    const std::vector<LLTableIndex>& row;

public:
    LLRowAccessor(const std::vector<LLTableIndex>& r)
        : row(r)
    {
    }

    LLTableIndex operator[](const Token& t) const;
};

class LLTable
{
private:
    //TODO: dodelat polozky pro expression-FuncName (obecne pro predavani precedencky prediktivce)
    static const std::vector<std::vector<LLTableIndex>> table;

public:
    LLRowAccessor operator[](const Nonterminal& nt) const;
};