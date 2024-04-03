/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-04-03 18:13
 */

#pragma once

typedef enum expressionType
{
    Unary,
    Binary
} ExpressionType;

class Expression
{
protected:
    ExpressionType type;
};