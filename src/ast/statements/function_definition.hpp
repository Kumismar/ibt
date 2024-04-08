/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:30
 * @ Modified time: 2024-04-08 22:40
 */

#pragma once

#include "code_block.hpp"
#include "statement.hpp"
#include "token.hpp"
#include <string>

class Parameter
{
private:
    std::string name;
    TokenType type;

public:
    void SetType(const TokenType type);
    void SetName(const std::string& name);
};

class FunctionDefinition : public Statement
{
private:
    Parameter* currentParam = nullptr;
    std::string name;
    DataType returnType;
    std::list<Parameter*> params;
    StatementList* body = nullptr;

    bool isType(const Token& token) const;
    void setReturnType(const Token& token);

public:
    FunctionDefinition();
    ~FunctionDefinition() override;
    void ProcessToken(Token& token) override;
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};