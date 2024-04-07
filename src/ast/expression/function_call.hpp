/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:10
 * @ Modified time: 2024-04-07 15:38
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"
#include <string>
#include <vector>

class FunctionCall : public Operand
{
private:
    std::string name;
    std::vector<Expression*> arguments;
};