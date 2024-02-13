#include "predictive.hpp"
#include "change_parser.hpp"
#include "grammar_factory.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

bool PredictiveParser::returnedEpsilon(std::list<StackItem*>& expandedRule)
{
    if (expandedRule.size() == 1 && expandedRule.front()->GetItemType() == Token_t) {
        Token* t = dynamic_cast<Token*>(expandedRule.front());
        return *t == Token(tEps);
    }
    return false;
}

void PredictiveParser::InitSyntaxAnalysis()
{
    this->pushdown.push(new Token(tEnd));
    this->pushdown.push(new Nonterminal(nProgram));
}

void PredictiveParser::Parse(std::list<Token>& inputTape)
{
    while (!this->success) {
        this->stackTop = this->pushdown.top();
        if (inputTape.empty()) {
            throw SyntaxErrorException("Missing token.\n");
        }
        this->inputToken = inputTape.front();

        switch (this->stackTop->GetItemType()) {
            case Token_t: {
                Token* stackToken = dynamic_cast<Token*>(this->stackTop);

                // Case $:
                if (stackToken->GetTokenType() == tEnd) {
                    if (this->inputToken.GetTokenType() == tEnd) {
                        this->success = true;
                        break;
                    }
                    else {
                        throw SyntaxErrorException("");
                    }
                }

                // Case T:
                if (stackToken->GetTokenType() == inputToken.GetTokenType()) {
                    this->pushdown.pop();
                    delete this->stackTop;
                    inputTape.pop_front();
                }
                else {
                    throw SyntaxErrorException("Unexpected token.\n");
                }
                break;
            }
            // Case N:
            case Nonterminal_t: {
                Nonterminal* stackNT = dynamic_cast<Nonterminal*>(this->stackTop);
                if (stackNT == nullptr) {
                    throw InternalErrorException("Dynamic cast to nonterminal failed\n");
                }

                // Expression => give control to precedence parser
                if (stackNT->GetNonterminalType() == nExpression) {
                    throw ChangeParser();
                }

                LLTableIndex tableItem = this->table[*stackNT][this->inputToken];
                // Rule exists -> pop old nonterminal, expand it and push new string to the stack
                if (tableItem != LLTableIndex({ 0, 0 })) {
                    Grammar* grammar = GrammarFactory::CreateGrammar(tableItem.grammarNumber);
                    this->pushdown.pop();
                    delete this->stackTop;
                    std::list<StackItem*> expandedRule = grammar->Expand(tableItem.ruleNumber);

                    if (this->returnedEpsilon(expandedRule)) {
                        throw InternalErrorException("Rule expansion returned epsilon\n");
                    }

                    for (StackItem* item: expandedRule) {
                        this->pushdown.push(item);
                    }

                    // TODO: print(rule)
                    delete grammar;
                }
                else {
                    throw SyntaxErrorException("Rule not found in LL table\n");
                }
                break;
            }
            default: {
                throw InternalErrorException("Unexpected item type: " + std::to_string(static_cast<int>(this->stackTop->GetItemType())) + "\n");
            }
        }
    }
}