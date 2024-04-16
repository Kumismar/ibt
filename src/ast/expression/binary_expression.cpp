/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-16 13:08
 */

#include "binary_expression.hpp"
#include "ast.hpp"
#include "expression.hpp"
#include "token.hpp"

BinaryExpression::BinaryExpression(TokenType t)
{
    AST* ast = AST::GetInstance();
    this->type = Binary;
    this->right = ast->GetExpressionContext();
    ast->PopExpressionContext();
    this->left = ast->GetExpressionContext();
    ast->PopExpressionContext();
    this->optr = new Operator(t);
}

BinaryExpression::~BinaryExpression()
{
    delete this->left;
    delete this->optr;
    delete this->right;
}

void BinaryExpression::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"BinaryExpression\"];\n";

    this->left->PrintTree(file, id, currentId);
    this->optr->PrintTree(file, id, currentId);
    this->right->PrintTree(file, id, currentId);
}

void BinaryExpression::ProcessToken(Token& token)
{
    return;
}

void BinaryExpression::LinkNode(ASTNode* node, Nonterminal& nt)
{
    return;
}
