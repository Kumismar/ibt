/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:23
 * @ Modified time: 2024-05-01 12:38
 */

#pragma once

#include "expression.hpp"
#include "token.hpp"

/**
 * @brief An enumeration for the type of the operand.
 */
typedef enum operandType
{
    Constant_t,
    Variable_t,
    FunctionCall_t
} OperandType;

/**
 * @brief A class representing an operand in the AST.
 */
class Operand : public Expression
{
protected:
    /**
     * @brief Type of the operand.
     */
    OperandType type;

    /**
     * @brief Data of the operand taken from token.
     */
    TokenData data;
};