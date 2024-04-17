/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 14:28
 * @ Modified time: 2024-04-17 16:13
 */

#include "ast_node_factory.hpp"
#include "ast.hpp"
#include "ast_node.hpp"
#include "declaration.hpp"
#include "elseif_statement.hpp"
#include "for_loop.hpp"
#include "function_definition.hpp"
#include "if_statement.hpp"
#include "nonterminal.hpp"
#include "return_statement.hpp"
#include "semicolon.hpp"
#include "statement_list.hpp"
#include "token.hpp"
#include "while_loop.hpp"

ASTNode* ASTNodeFactory::CreateASTNode(Nonterminal& nt, Token& t)
{
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
                case tInt:
                case tBool:
                case tString:
                case tFloat: {
                    return new Declaration();
                }
                default: {
                    return nullptr;
                }
            }
        }
        case nIf2: {
            return new ElseifStatement();
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