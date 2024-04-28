/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 15:41
 * @ Modified time: 2024-04-28 16:07
 */

#pragma once

#include "token.hpp"

class EndInsertor
{
private:
    void skipFunctionCall(InputTape::iterator& token) const;
    void skipOperand(InputTape::iterator& token) const;
    void skipOperandInParentheses(InputTape::iterator& token) const;
    bool isOperator(Token& token) const;

public:
    void InsertExpressionEnd() const;
    void InsertFunctionEnd() const;
};
