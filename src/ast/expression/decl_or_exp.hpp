/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:43
 * @ Modified time: 2024-04-03 17:56
 */

#pragma once

#include "declaration.hpp"
#include "expression.hpp"

typedef union
{
    Declaration* decl;
    Expression* exp;
} DeclOrExp;