/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:14
 * @ Modified time: 2024-04-03 18:21
 */

#pragma once

#include "operand.hpp"
#include "token.hpp"

class Constant : public Operand
{
private:
    OperandData data;
};