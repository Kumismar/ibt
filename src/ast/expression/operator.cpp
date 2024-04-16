/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-16 11:41
 * @ Modified time: 2024-04-16 13:10
 */

#include "operator.hpp"
#include "internal_error.hpp"
#include "token.hpp"
#include <fstream>

Operator::Operator(TokenType t)
{
    switch (t) {
        case tPlus: {
            this->type = Plus;
            break;
        }
        case tMinus: {
            this->type = Minus;
            break;
        }
        case tMul: {
            this->type = Multiply;
            break;
        }
        case tDiv: {
            this->type = Divide;
            break;
        }
        case tConcat: {
            this->type = Concat;
            break;
        }
        case tAssign: {
            this->type = Assign;
            break;
        }
        case tEq: {
            this->type = Equal_ot;
            break;
        }
        case tNEq: {
            this->type = NotEqual;
            break;
        }
        case tLess: {
            this->type = Less;
            break;
        }
        case tLEq: {
            this->type = LessEqual;
            break;
        }
        case tGreater: {
            this->type = Greater;
            break;
        }
        case tGEq: {
            this->type = GreaterEqual;
            break;
        }
        case tAnd: {
            this->type = And;
            break;
        }
        case tOr: {
            this->type = Or;
            break;
        }
        case tExcl: {
            this->type = Not;
            break;
        }
        case tUnMinus: {
            this->type = UnaryMinus;
            break;
        }
        default: {
            throw InternalError("Operator::Operator invalid token type, realtype: " + std::to_string(t));
        }
    }
}

OperatorType Operator::GetType() const
{
    return this->type;
}

void Operator::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"";
    switch (this->type) {
        case Plus: {
            file << "+";
            break;
        }
        case UnaryMinus:
        case Minus: {
            file << "-";
            break;
        }
        case Multiply: {
            file << "*";
            break;
        }
        case Divide: {
            file << "/";
            break;
        }
        case Concat: {
            file << ".";
            break;
        }
        case Assign: {
            file << "=";
            break;
        }
        case Equal_ot: {
            file << "==";
            break;
        }
        case NotEqual: {
            file << "!=";
            break;
        }
        case Less: {
            file << "<";
            break;
        }
        case LessEqual: {
            file << "<=";
            break;
        }
        case Greater: {
            file << ">";
            break;
        }
        case GreaterEqual: {
            file << ">=";
            break;
        }
        case And: {
            file << "&&";
            break;
        }
        case Or: {
            file << "||";
            break;
        }
        case Not: {
            file << "!";
            break;
        }
        default: {
            throw InternalError("Operator::PrintTree invalid operator type: " + std::to_string(this->type));
        }
    }
    file << "\"];\n";
}