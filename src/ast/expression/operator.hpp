/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:25
 * @ Modified time: 2024-04-03 18:39
 */

#pragma once

typedef enum operatorType
{
    Plus,
    Minus,
    Multiply,
    Divide,
    Concat,
    Assign,
    Equal,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    And,
    Or,
    Not,
    UnaryMinus,
} OperatorType;

class Operator
{
private:
    OperatorType type;
};