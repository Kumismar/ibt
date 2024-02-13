#include "change_parser.hpp"
#include "grammar_1.hpp"
#include "grammar_2.hpp"
#include "grammar_3.hpp"
#include "grammar_4.hpp"
#include "grammar_5.hpp"
#include "grammar_6.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "parser.hpp"
#include "precedence.hpp"
#include "predictive.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <iostream>
#include <list>
#include <pthread.h>
#include <stack>

void Cleanup()
{
    Grammar1::Cleanup();
    Grammar2::Cleanup();
    Grammar3::Cleanup();
    Grammar4::Cleanup();
    Grammar5::Cleanup();
    Grammar6::Cleanup();
}

void processArguments(int argc, char** argv)
{
}

int main(int argc, char** argv)
{
    processArguments(argc, argv);

    std::stack<StackItem*> predictiveStack;
    std::stack<Expression*> precedenceStack;
    std::list<Token> inputTape = {
        // Token(tIf), Token(tLPar), Token(tVariable), Token(tRPar), Token(tLCurl), Token(tRCurl)
        Token(tVariable)
    };

    PrecedenceParser exprParser(precedenceStack);
    PredictiveParser predParser(predictiveStack);
    predParser.InitSyntaxAnalysis();
    Parser* currentParser = static_cast<Parser*>(&predParser);
    currentParser->SetParserType(Predictive);

    int retCode = 0;

    while (true) {
        try {
            currentParser->Parse(inputTape);
            if (inputTape.empty()) {
                std::cout << "Parsing successful" << std::endl;
                break;
            }
            else {
                throw SyntaxErrorException("");
            }
        }
        catch (ChangeParser const& e) {
            if (currentParser->GetParserType() == Predictive) {
                currentParser = static_cast<Parser*>(&exprParser);
            }
            else {
                currentParser = static_cast<Parser*>(&predParser);
            }
            continue;
        }
        catch (SyntaxErrorException const& e) {
            std::cerr << "Syntax error: " << e.what() << std::endl;
            retCode = 1;
            break;
        }
        catch (InternalErrorException const& e) {
            std::cerr << "Internal error: " << e.what() << std::endl;
            retCode = 2;
            break;
        }
    }

    Cleanup();
    return retCode;
}