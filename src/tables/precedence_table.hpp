/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#pragma once

#include "token.hpp"
#include <vector>

#define ROWSIZE 19

class PrecRowAccessor
{
private:
    const std::vector<char>& row;

public:
    PrecRowAccessor(const std::vector<char>& r)
        : row(r)
    {
    }

    char operator[](const Token& t);
};

class PrecedenceTable
{
private:
    static const std::vector<std::vector<char>> precTable;

public:
    PrecRowAccessor operator[](const Token& t) const;
    static unsigned MapTokenToIndex(const Token& t);
};