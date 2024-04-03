/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:23
 * @ Modified time: 2024-04-03 18:20
 */

#pragma once

#include "token.hpp"
typedef enum operandType
{
    Constant,
    Variable,
    FunctionCall
} OperandType;

typedef struct OperandData {
    DataType type;
    Value value;
} OperandData;

class Operand
{
protected:
    OperandType type;

public:
    virtual ~Operand()
    {
    }
};