#pragma once

typedef enum tokenType
{
    tIf,
    tWhile,
    tFor,
    tReturn,
    tSemi,
    tElseif,
    tElse,
    tLPar,
    tRPar,
    tLCurl,
    tRCurl,
    tFunction,
    tFuncName,
    tColon,
    tVariable,
    tPLus,
    tMinus,
    tMul,
    tDiv,
    tConcat,
    tExcl,
    tAnd,
    tOr,
    tEq,
    tNEq,
    tConst,
    tComma,
    tInt,
    tFloat,
    tString,
    tBool,
    tEps,
    tEnd
} TokenType;