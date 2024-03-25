/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 17:37
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