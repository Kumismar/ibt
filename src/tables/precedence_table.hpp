#pragma once

#include "token.hpp"
#include <vector>

class PrecRowAccessor
{
private:
    const std::vector<char>& precTableRow;

public:
    PrecRowAccessor(const std::vector<char>& r)
        : precTableRow(r)
    {
    }

    char operator[](const Token& t);
};

class PrecedenceTable
{
private:
    const std::vector<std::vector<char>> precTable = {
        // +    -    *    /    .   &&   ||   ==   !=    >    <   >=   <=    (    )    !  un -   $    i
        { '>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // +
        { '>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // -
        { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // *
        { '>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // /
        { '>', '>', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // .
        { '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // &&
        { '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // ||
        { '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // ==
        { '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // !=
        { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // >
        { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // <
        { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // >=
        { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '<', '>', '<', '<', '>', '<' }, // <=
        { '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', '<', '>', '<' }, // (
        { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'x', '>', 'x', 'x', '>', 'x' }, // )
        { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '>', '>', '>', '<' }, // !
        { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '>', '>', '>', '<' }, // unary -
        { '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', 'x', '<', '<', 'x', '<' }, // $
        { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'x', '>', 'x', 'x', '>', 'x' }, // i
    };

public:
    PrecRowAccessor operator[](const Token& t);
};