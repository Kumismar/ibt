/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

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
    static const std::vector<std::vector<LLTableIndex>> table;

public:
    LLRowAccessor operator[](const Nonterminal& nt) const;
};