#include "predictive.hpp"
#include "grammar_factory.hpp"
#include "ll_table.hpp"
#include "precedence.hpp"
#include <iostream>

void PredictiveParser::Parse(std::list<Token>& inputTape)
{
    LLTable llTable;

    while (!this->success && !this->fail) {
        this->stackTop = this->pushdown.top();
        this->inputToken = inputTape.front();

        switch (this->stackTop.GetItemType()) {
            case Token_t: {
                Token& stackToken = dynamic_cast<Token&>(this->stackTop);

                // Case $:
                if (stackToken.GetTokenType() == tEnd) {
                    if (this->inputToken.GetTokenType() == tEnd) {
                        this->success = true;
                        break;
                    }
                    else {
                        this->fail = true;
                        break;
                    }
                }

                // Case T:
                if (stackToken.GetTokenType() == inputToken.GetTokenType()) {
                    this->pushdown.pop();
                    inputTape.erase(inputTape.begin());
                    this->inputToken = inputTape.front();
                }
                else {
                    this->fail = true;
                }
                break;
            }
            // Case N:
            case Nonterminal_t: {
                Nonterminal& stackNT = dynamic_cast<Nonterminal&>(this->stackTop);
                LLTableIndex tableItem = llTable[stackNT][this->inputToken];

                // Expression => give control to precedence parser and pop expression nonterminal
                if (stackNT.GetNonterminalType() == nExpression) {
                    PrecedenceParser p;
                    p.Parse(inputTape);
                    this->pushdown.pop();
                    break;
                }
                else if (tableItem != LLTableIndex({ 0, 0 })) { // Rule exist
                    Grammar* grammar = GrammarFactory::CreateGrammar(tableItem.grammarNumber); // TODO: Might return nullptr (shouldnt)
                    this->pushdown.pop();
                    std::list<StackItem> tmp = grammar->Expand(tableItem.ruleNumber); // TODO: Might return empty list or epsilon only (shouldnt)
                    for (StackItem& item: tmp) {
                        this->pushdown.push(item);
                    }
                    // TODO: print(rule)
                    delete grammar;
                }
                else {
                    this->fail = true;
                }
                break;
            }
            default: {
            }
        }
    }

    if (this->fail) {
        std::cerr << "parsing failed" << std::endl;
    }
    else if (this->success) {
        std::cout << "parsing success" << std::endl;
    }
}