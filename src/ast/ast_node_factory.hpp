/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 14:27
 * @ Modified time: 2024-04-28 16:46
 */

#pragma once

#include "ast_node.hpp"
#include "expression.hpp"
#include "grammar.hpp"
#include "nonterminal.hpp"
#include "token.hpp"

class ASTNodeFactory
{
private:
    Expression* createOperand(Rule& rule);
    Expression* createUnaryExpression(Rule& rule);
    Expression* createBinaryExpression(Rule& rule);

    bool isUnaryExpression(Rule& rule);

public:
    static ASTNode* CreateASTNode(Nonterminal& nt, Token& t);
    Expression* CreateASTNode(Rule& rule);
};