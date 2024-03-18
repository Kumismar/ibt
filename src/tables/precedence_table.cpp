/**
 * @author Ondřej Koumar (xkouma02@stud.fit.vutbr.cz)
 * @date 2024-03-18
 */

#include "precedence_table.hpp"
#include "internal_error.hpp"
#include "token.hpp"

const std::vector<std::vector<char>> PrecedenceTable::precTable = {
    // +    -    *    /    .   &&   ||   ==   !=    >    <   >=   <=    =    (    )    !    $    i   un-
    { '>', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // +
    { '>', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // -
    { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // *
    { '>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // /
    { '>', '>', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // .
    { '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // &&
    { '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // ||
    { '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // ==
    { '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // !=
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // >
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // <
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // >=
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '<' }, // <=
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', 'x', '<', '<', '<', '>', '<', '<' }, // =
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', 'x', '<', '>' }, // (
    { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'x', '>', 'x', '>', 'x', '<' }, // )
    { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '>', '>', '<', 'x' }, // !
    { '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', 'x', '<', 'x', '<', '<' }, // $
    { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', 'x', '>', 'x', '>', 'x', '>' }, // i
    { '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', 'x', '>', '<', '<' } // un-
};

char PrecRowAccessor::operator[](const Token& t)
{
    unsigned colIndex = PrecedenceTable::MapTokenToIndex(t);
    return this->row[colIndex];
}

PrecRowAccessor PrecedenceTable::operator[](const Token& t) const
{
    unsigned rowIndex = this->MapTokenToIndex(t);
    return PrecRowAccessor(PrecedenceTable::precTable[rowIndex]);
}

unsigned PrecedenceTable::MapTokenToIndex(const Token& t)
{
    switch (t.GetTokenType()) {
        case tPlus:
            return 0;
        case tMinus:
            return 1;
        case tMul:
            return 2;
        case tDiv:
            return 3;
        case tConcat:
            return 4;
        case tAnd:
            return 5;
        case tOr:
            return 6;
        case tEq:
            return 7;
        case tNEq:
            return 8;
        case tGreater:
            return 9;
        case tLess:
            return 10;
        case tGEq:
            return 11;
        case tLEq:
            return 12;
        case tAssign:
            return 13;
        case tLPar:
            return 14;
        case tRPar:
            return 15;
        case tExcl:
            return 16;
        case tExpEnd:
            return 17;
        // funcName will be changed for tConst on stack
        case tConst:
        case tVariable:
            return 18;
        case tUnMinus:
            return 19;
        default:
            throw InternalErrorException("PrecedenceTable::MapTokenToIndex invalid token type");
    }
}