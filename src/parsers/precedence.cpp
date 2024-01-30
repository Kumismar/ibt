#include "precedence.hpp"
#include "precedence_symbol.hpp"
#include "precedence_table.hpp"

void PrecedenceParser::Parse(std::list<Token>& inputTape)
{
    PrecedenceTable table;
    this->expStack.push(Token(tEnd));
    do {
        this->top = expStack.top();
        Token& input = inputTape.front();
        inputTape.pop_front();

        switch (table[this->top][input]) {
            case '=': {
                expStack.push(input);
                input = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '<': {
                expStack.push(PrecedenceSymbol('<'));
                expStack.push(input);
                input = inputTape.front();
                inputTape.pop_front();
                break;
            }
            case '>': {
                this->top = expStack.top();
                this->second = this->getSecondFromStack();
            }
        }

    } while (!this->success && !this->fail);
}

Expression& PrecedenceParser::getSecondFromStack()
{
    Expression& tmp = expStack.top();
    expStack.pop();
    Expression& second = expStack.top();
    expStack.push(tmp);
    return second;
}