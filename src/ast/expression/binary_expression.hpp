/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:22
 * @ Modified time: 2024-04-03 17:55
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"
#include "operator.hpp"

class BinaryExpression : Expression
{
private:
    Operand* left = nullptr;
    Operator* optr = nullptr;
    Operand* right = nullptr;
};