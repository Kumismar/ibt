/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:26
 * @ Modified time: 2024-04-03 17:56
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"
#include "operator.hpp"

class UnaryExpression : public Expression
{
private:
    Operator* optr = nullptr;
    Operand* operand = nullptr;
};