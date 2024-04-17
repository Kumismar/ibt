/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:25
 * @ Modified time: 2024-04-16 13:08
 */

#pragma once

#include "token.hpp"
typedef enum operatorType
{
    Plus,
    Minus,
    Multiply,
    Divide,
    Concat,
    Assign,
    Equal_ot,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    And,
    Or,
    Not,
    UnaryMinus,
    ExpInParentheses
} OperatorType;

class Operator
{
private:
    OperatorType type;

public:
    OperatorType GetType() const;
    Operator(TokenType t);
    void PrintTree(std::ofstream& file, int& id, int parentId);
};