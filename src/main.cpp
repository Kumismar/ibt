#include "change_parser.hpp"
#include "grammar_1.hpp"
#include "grammar_2.hpp"
#include "grammar_3.hpp"
#include "grammar_4.hpp"
#include "grammar_5.hpp"
#include "grammar_6.hpp"
#include "internal_error.hpp"
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

    std::stack<StackItem*> stackos;
    std::list<Token> inputTape = {
        // Token(tIf), Token(tLPar), Token(tVariable), Token(tRPar), Token(tLCurl), Token(tRCurl)
        Token(tVariable), Token(tAssign), Token(tVariable), Token(tSemi)
    };

    PrecedenceParser exprParser(stackos);
    PredictiveParser predParser(stackos);
    predParser.InitSyntaxAnalysis();
    Parser* currentParser = static_cast<Parser*>(&predParser);
    currentParser->SetParserType(Predictive);

    int retCode = 0;

    while (true) {
        try {
            //TODO: Kdyz precedencka skonci, tak se to dostane k vyhozeni vyjimky
            currentParser->Parse(inputTape);
            if (inputTape.empty()) {
                std::cout << "Parsing successful" << std::endl;
                break;
            }
            else {
                throw SyntaxErrorException("Tokens left in input tape");
            }
        }
        catch (ChangeParser const& e) {
            if (currentParser->GetParserType() == Predictive) {
                currentParser = static_cast<Parser*>(&exprParser);
                currentParser->SetParserType(Precedence);
            }
            else {
                currentParser = static_cast<Parser*>(&predParser);
                currentParser->SetParserType(Predictive);
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