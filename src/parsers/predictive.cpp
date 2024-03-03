#include "predictive.hpp"
#include "analysis_success.hpp"
#include "change_parser.hpp"
#include "grammar_factory.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "stack_item.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

bool PredictiveParser::returnedEpsilon(std::list<StackItem*>& expandedRule)
{
    if (expandedRule.size() == 1 && expandedRule.front()->GetItemType() == Token_t) {
        Token* t = dynamic_cast<Token*>(expandedRule.front());
        return *t == tEps;
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
    Logger* logger;
    while (true) {
        this->stackTop = this->pushdown.top();
        if (inputTape.empty()) {
            throw SyntaxErrorException("Missing token(s).\n");
        }
        this->inputToken = inputTape.front();

        switch (this->stackTop->GetItemType()) {
            case Token_t: {
                Token* stackToken = dynamic_cast<Token*>(this->stackTop);
                if (stackToken == nullptr) {
                    throw InternalErrorException("Dynamic cast to Token* failed\n");
                }

                // Case $:
                if (stackToken->GetTokenType() == tEnd) {
                    if (this->inputToken.GetTokenType() == tEnd) {
                        // tEnd was pushed as new Token, its not a pointer to something in grammars or tables
                        delete stackToken;
                        inputTape.pop_front();

                        if (inputTape.empty()) {
                            throw SyntaxAnalysisSuccess();
                        }
                        else {
                            throw InternalErrorException("Popped tEnd from input tape but there is still something left\n");
                        }
                    }
                    else {
                        throw SyntaxErrorException("Unexpected token (expected End)\n");
                    }
                }

                // Case T:
                if (*stackToken == inputToken) {
                    this->pushdown.pop();
                    inputTape.pop_front();
                    break;
                }
                else {
                    throw SyntaxErrorException("Unexpected token.\n");
                }
            }
            // Case N:
            case Nonterminal_t: {
                Nonterminal* stackNT = dynamic_cast<Nonterminal*>(this->stackTop);
                if (stackNT == nullptr) {
                    throw InternalErrorException("Dynamic cast to Nonterminal* failed\n");
                }

                // Expression => give control to precedence parser
                if (stackNT->GetNonterminalType() == nExpression && inputToken != tFuncName) {
                    throw ChangeParser();
                }

                LLTableIndex tableItem = this->table[*stackNT][this->inputToken];
                // Rule exists -> pop old nonterminal, expand it and push new string to the stack
                if (tableItem != LLTableIndex({ 0, 0 })) {
                    logger = Logger::GetInstance();
                    logger->AddLeftSide(this->stackTop);
                    Grammar* grammar = GrammarFactory::CreateGrammar(tableItem.grammarNumber);

                    this->pushdown.pop();

                    std::list<StackItem*> expandedRule = grammar->Expand(tableItem.ruleNumber);

                    // if right side is not epsilon, it will be pushed
                    if (!this->returnedEpsilon(expandedRule)) {
                        for (StackItem* item: expandedRule) {
                            this->pushdown.push(item);
                        }
                    }

                    logger->AddRightSide(expandedRule);
                    logger->PrintRule();

                    if (*stackNT == nProgram) {
                        // Program was pushed as new Nonterminal, its not a pointer to something in grammars or tables
                        delete stackNT;
                    }
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