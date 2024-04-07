/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 15:42
 * @ Modified time: 2024-04-07 15:42
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"

class SingleOperandExpresion : public Expression
{
private:
    Operand* operand;
};