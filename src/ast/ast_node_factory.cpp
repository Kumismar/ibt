/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-07 14:28
 * @ Modified time: 2024-04-07 20:32
 */

#include "ast_node_factory.hpp"
#include "ast_node.hpp"
#include "code_block.hpp"
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
                case tSemi: {
                    return new Semicolon();
                }
                // case tLPar:
                // case tFuncName:
                // case tVariable:
                // case tUnMinus:
                // case tExcl:
                // case tConst: {
                //     return new Expression();
                // }
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
            if (t.GetTokenType() == tElseif) {
                return new ElseifStatement();
            }
            else {
                return nullptr;
            }
        }
        case nStatements: {
            return new StatementList();
        }
        case nFunctionDef: {
            return new FunctionDefinition();
        }
        // case nExpression: {
        //     return new Expression();
        // }
        case nCodeBlock: {
            return new CodeBlock();
        }

        default: {
            return nullptr;
        }
    }
}