/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 14:28
 * @ Modified time: 2024-04-29 11:53
 */

#include "ast_node_factory.hpp"
#include "ast.hpp"
#include "ast_node.hpp"
#include "binary_expression.hpp"
#include "constant.hpp"
#include "declaration.hpp"
#include "elseif_statement.hpp"
#include "for_loop.hpp"
#include "function_definition.hpp"
#include "if_statement.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "return_statement.hpp"
#include "statement_list.hpp"
#include "token.hpp"
#include "unary_expression.hpp"
#include "variable.hpp"
#include "while_loop.hpp"

ASTNode* ASTNodeFactory::CreateASTNode(Nonterminal& nt, Token& t)
{
    if (AST::GetInstance()->IsTurnedOff()) {
        return nullptr;
    }

    switch (nt.GetNonterminalType()) {
        case nStatement: {
            switch (t.GetTokenType()) {
                case tIf: {
                    return new IfStatement();
                }
                case tWhile: {
                    return new WhileLoop();
                }
                case tFor: {
                    return new ForLoop();
                }
                case tReturn: {
                    return new ReturnStatement();
                }
                default: {
                    return nullptr;
                }
            }
        }
        case nDeclOrExpr: {
            switch (t.GetTokenType()) {
                case tInt:
                case tFloat:
                case tString:
                case tBool: {
                    return new Declaration();
                }
                default: {
                    return nullptr;
                }
            }
        }
        case nIf2: {
            if (t.GetTokenType() == tElseif) {
                return new ElseifStatement();
            }
            return nullptr;
        }
        case nFunctionDef: {
            return new FunctionDefinition();
        }
        case nCodeBlock: {
            return new StatementList();
        }
        case nStatements: {
            if (AST::GetInstance()->GetCurrentContext()->GetNodeType() == FuncDef_n) {
                return new StatementList();
            }
            return nullptr;
        }
        default: {
            return nullptr;
        }
    }
}
Expression* ASTNodeFactory::CreateASTNode(Rule& rule)
{
    //right side is either variable, const or funcConst
    if (AST::GetInstance()->IsTurnedOff()) {
        return nullptr;
    }

    if (rule.size() == 1) {
        return this->createOperand(rule);
    }
    else if (this->isUnaryExpression(rule)) {
        return this->createUnaryExpression(rule);
    }
    else if (rule.size() == 3) {
        return this->createBinaryExpression(rule);
    }
    else {
        throw InternalError("ASTNodeFactory:: rule size != {1, 2, 3}\n");
    }
}

bool ASTNodeFactory::isUnaryExpression(Rule& rule)
{
    if (rule.size() == 2) {
        return true;
    }

    auto* tmp = dynamic_cast<Token*>(rule.front());
    if (tmp != nullptr) {
        return (*tmp == tLPar);
    }
    return false;
}

Expression* ASTNodeFactory::createOperand(Rule& rule)
{
    Symbol* tmpSymb = rule.front();
    auto* operandToken = dynamic_cast<Token*>(tmpSymb);
    if (operandToken == nullptr) {
        throw InternalError("ASTNodeFactory::createOperand operand is not Token*, real type:" + std::string(typeid(*tmpSymb).name()) + "\n");
    }

    if (*operandToken == tVariable) {
        auto* tmpVar = new Variable(*operandToken);
        return tmpVar;
    }
    else if (*operandToken == tConst) {
        auto* tmpConst = new Constant(*operandToken);
        return tmpConst;
    }
    else if (*operandToken == tFuncConst) {
        // Function call node was already created, just return
        return nullptr;
    }
    else {
        throw InternalError("ASTNodeFactory::createOperand token is not var or const\n");
    }
}

Expression* ASTNodeFactory::createUnaryExpression(Rule& rule)
{
    Symbol* tmpSymb = *rule.begin();
    auto* optr = dynamic_cast<Token*>(tmpSymb);
    if (optr == nullptr) {
        throw InternalError("ASTNodeFactory::createUnaryExpression optr is not Token*, real type:" + std::string(typeid(*tmpSymb).name()) + "\n");
    }

    Expression* tmpExp = new UnaryExpression(optr->GetTokenType());
    return tmpExp;
}

Expression* ASTNodeFactory::createBinaryExpression(Rule& rule)
{
    Token* possibleLPar = dynamic_cast<Token*>(*rule.begin());
    if (possibleLPar != nullptr && *possibleLPar == tLPar) {
        auto* tmpExp = new UnaryExpression(tLPar);
        return tmpExp;
    }

    Symbol* tmpSymb = *std::next(rule.begin());
    auto* optr = dynamic_cast<Token*>(tmpSymb);
    if (optr == nullptr) {
        throw InternalError("ASTNodeFactory::createBinaryExpression optr is not Token*, real type:" + std::string(typeid(*tmpSymb).name()) + "\n");
    }

    auto* tmpExp = new BinaryExpression(optr->GetTokenType());
    return tmpExp;
}
