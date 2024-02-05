#include "precedence.hpp"
#include "precedence_symbol.hpp"
#include "precedence_table.hpp"

void PrecedenceParser::Parse(std::list<Token>& inputTape)
{
    PrecedenceTable table;
    this->expStack.push(Token(tEnd));
    do {
        this->top = expStack.top();
        Token& inputToken = inputTape.front();
        inputTape.pop_front();

        Token& firstToken = this->findFirstTokenInStack();
        switch (table[firstToken][inputToken]) {
            case '=': {
                expStack.push(inputToken);
                inputToken = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '<': {
                expStack.push(PrecedenceSymbol('<'));
                expStack.push(inputToken);
                inputToken = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '>': {
                std::list<Expression>& tmpRule = this->findFirstRule();
            }
        }

    } while (!this->success && !this->fail);
}

std::list<Expression>& PrecedenceParser::findFirstRule()
{
    std::list<Expression> toReturn;
    Expression tmpTop = this->expStack.top();
    // push to list until stack.top is precedence symbol '<'
    while (true) {
        if (tmpTop.GetExpressionType() == ExpPrecSymbol) {
            PrecedenceSymbol& tmpSymbol = dynamic_cast<PrecedenceSymbol&>(tmpTop);
            if (tmpSymbol == Push) {
                break;
            }
            // else error
        }
        else {
            toReturn.push_front(tmpTop);
            this->expStack.pop();
        }
    }
    return toReturn;
}

Expression& PrecedenceParser::getSecondFromStack()
{
    Expression& tmp = expStack.top();
    expStack.pop();
    Expression& second = expStack.top();
    expStack.push(tmp);
    return second;
}

Token& PrecedenceParser::findFirstTokenInStack()
{
    std::stack<Expression> tmpStack;
    Expression tmpExp;
    while ((tmpExp = this->expStack.top()).GetExpressionType() != ExpToken) {
        tmpStack.push(tmpExp);
        this->expStack.pop();
    }
    while (!tmpStack.empty()) {
        Expression tmpExp2 = tmpStack.top();
        tmpStack.pop();
        this->expStack.push(tmpExp2);
    }

    return dynamic_cast<Token&>(tmpExp);
}