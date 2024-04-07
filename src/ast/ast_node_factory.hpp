/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 14:27
 * @ Modified time: 2024-04-07 14:44
 */

#pragma once

#include "ast_node.hpp"
#include "nonterminal.hpp"
#include "token.hpp"

class ASTNodeFactory
{
public:
    static ASTNode* CreateASTNode(Nonterminal& nt, Token& t);
};