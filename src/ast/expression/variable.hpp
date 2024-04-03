/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:21
 * @ Modified time: 2024-04-03 18:22
 */

#pragma once

#include "operand.hpp"

class Variable : public Operand
{
private:
    std::string name;
    OperandData data;
};