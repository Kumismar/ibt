/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:30
 * @ Modified time: 2024-04-07 16:47
 */

#pragma once

#include "statement.hpp"
#include "statement_list.hpp"
#include "token.hpp"
#include <string>
#include <vector>

class Parameter
{
private:
    std::string name;
    DataType type;
};

class FunctionDefinition : public Statement
{
private:
    std::string name;
    std::vector<Parameter*> params;
    StatementList* body = nullptr;

public:
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};