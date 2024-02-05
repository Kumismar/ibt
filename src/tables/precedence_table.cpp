#include "precedence_table.hpp"

char PrecRowAccessor::operator[](const Token& t){
    unsigned colIndex =
}

PrecRowAccessor PrecedenceTable::operator[](const Token& t) const
{
    unsigned rowIndex = this->MapTokenToIndex(t);
    return PrecRowAccessor(this->precTable[rowIndex]);
}

static unsigned PrecedenceTable::MapTokenToIndex(const Token& t)
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
        case tLPar:
            return 13;
        case tRPar:
            return 13;
        case tExcl:
            return 14;
        case tUnMinus:
            return 15;
        case tEnd:
            return 16;
        case tId:
            return 17;
        default:
            return 100;
    }
}