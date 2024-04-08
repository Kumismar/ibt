/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:21
 * @ Modified time: 2024-04-08 12:51
 */

#pragma once

#include "operand.hpp"
#include "token.hpp"

class Variable : public Operand
{
private:
    std::string name;

public:
    Variable(Token& token);
    ~Variable() override;
};