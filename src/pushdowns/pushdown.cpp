#include "pushdown.hpp"
#include "grammar_factory.hpp"
#include "ll_table.hpp"

void PushdownAutomaton::Parse(std::list<Token>& inputTape)
{
    LLTable llTable;

    while (!this->success && !this->fail) {
        this->stackTop = this->pushdown.top();
        this->inputToken = inputTape.front();

        switch (this->stackTop.GetType()) {
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

                // Case T
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
                TableIndex tableItem = llTable[stackNT][this->inputToken];

                if (tableItem != TableIndex({ 0, 0 })) { // Rule exists
                    Grammar* grammar = GrammarFactory::CreateGrammar(tableItem.grammarNumber); // Might return nullptr (shouldnt)

                    // TODO: if its expression, then it has to transfer control to expression parsing
                    this->pushdown.pop();
                    std::list<StackItem> tmp = grammar->Expand(tableItem.ruleNumber); // Might return empty list or epsilon only (shouldnt)
                    for (StackItem& item: tmp) {
                        this->pushdown.push(item);
                    }
                    // print(rule)
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
}