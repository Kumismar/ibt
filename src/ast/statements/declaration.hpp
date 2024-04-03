/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:44
 * @ Modified time: 2024-04-03 17:57
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"
#include "statement.hpp"

class Declaration : public Statement
{
private:
    Operand* left = nullptr;
    Expression* right = nullptr;
};