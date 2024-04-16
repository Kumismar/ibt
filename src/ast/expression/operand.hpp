/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:23
 * @ Modified time: 2024-04-15 20:39
 */

#pragma once

#include "expression.hpp"
#include "token.hpp"
typedef enum operandType
{
    Constant_t,
    Variable_t,
    FunctionCall_t
} OperandType;


class Operand : public Expression
{
protected:
    OperandType type;
    TokenData data;

public:
    virtual ~Operand()
    {
    }
};