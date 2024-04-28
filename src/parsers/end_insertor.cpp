/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 15:42
 * @ Modified time: 2024-04-28 21:18
 */

#include "end_insertor.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

void EndInsertor::InsertExpressionEnd() const
{
    auto token = inputTape.begin();
    while (token != inputTape.end()) {
        // skip operand
        this->skipOperand(token);

        // if the operand was the last one, insert expEnd behind
        if (!this->isOperator(**token)) {
            break;
        }
        // skip operator
        token++;
    }

    if (token == inputTape.end()) {
        throw SyntaxError("Missing token(s).\n");
    }

    inputTape.insert(token, new Token(tExpEnd));
}

void EndInsertor::InsertFunctionEnd() const
{
    // go through inputTape and insert tFuncEnd after the first right parenthesis matched with left parenthesis
    int counter = 0;
    for (auto token = inputTape.begin(); token != inputTape.end(); token++) {
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter == 0 && **token == tRPar) {
            inputTape.insert(++token, new Token(tFuncEnd));
            return;
        }
    }
}

void EndInsertor::skipOperand(InputTape::iterator& token) const
{
    // skip unary operators
    while (**token == tUnMinus || **token == tExcl) {
        token++;
        if (token == inputTape.end()) {
            throw SyntaxError("Missing token(s).\n");
        }
    }

    if (**token == tLPar) {
        this->skipOperandInParentheses(token);
        return;
    }

    if (**token == tFuncName) {
        this->skipFunctionCall(token);
        return;
    }

    if (**token != tConst && **token != tVariable) {
        throw SyntaxError("Invalid token.\n");
    }

    token++;
    if (token == inputTape.end()) {
        throw SyntaxError("Missing token(s).\n");
    }
}

void EndInsertor::skipFunctionCall(InputTape::iterator& token) const
{
    int counter = 0;

    for (token++; (token != inputTape.end() && **token != tExpEnd); token++) {
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter == 0) {
            token++;
            return;
        }
    }

    if (token == inputTape.end() || **token == tExpEnd) {
        throw SyntaxError("Invalid token.\n");
    }
}

void EndInsertor::skipOperandInParentheses(InputTape::iterator& token) const
{
    int counter = 0;
    while (token != inputTape.end()) {
        if (**token == tLPar) {
            counter++;
        }
        else if (**token == tRPar) {
            counter--;
        }

        if (counter == 0) {
            break;
        }

        token++;
    }

    token++;
    if (token == inputTape.end()) {
        throw SyntaxError("Missing token(s).\n");
    }
}

bool EndInsertor::isOperator(Token& token) const
{
    return (token == tPlus || token == tMinus || token == tMul || token == tDiv || token == tConcat ||
            token == tAnd || token == tOr ||
            token == tEq || token == tNEq || token == tLess || token == tGreater || token == tLEq || token == tGEq ||
            token == tAssign);
}