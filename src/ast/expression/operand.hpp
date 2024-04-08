/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:23
 * @ Modified time: 2024-04-08 10:50
 */

#pragma once

#include "token.hpp"
typedef enum operandType
{
    Constant_t,
    Variable_t,
    FunctionCall_t
} OperandType;

typedef struct OperandData {
    DataType type;
    Value value;
} OperandData;

class Operand
{
protected:
    OperandType type;
    OperandData data;

public:
    virtual ~Operand()
    {
    }
};