#include "analysis_success.hpp"
#include "change_parser.hpp"
#include "grammar_1.hpp"
#include "grammar_2.hpp"
#include "grammar_3.hpp"
#include "grammar_4.hpp"
#include "grammar_5.hpp"
#include "grammar_6.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "precedence.hpp"
#include "predictive.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <iostream>
#include <list>
#include <stack>

void Cleanup()
{
    Grammar1::Cleanup();
    Grammar2::Cleanup();
    Grammar3::Cleanup();
    Grammar4::Cleanup();
    Grammar5::Cleanup();
    Grammar6::Cleanup();
    Logger::Cleanup();
}

void processArguments(int argc, char** argv)
{
}

int main(int argc, char** argv)
{
    processArguments(argc, argv);

    std::stack<StackItem*> stackos;
    std::list<Token> inputTape = {
        // Token(tIf), Token(tLPar), Token(tVariable), Token(tPlus), Token(tVariable), Token(tRPar), Token(tLCurl), Token(tRCurl), Token(tEnd)
        Token(tVariable), Token(tAssign), Token(tVariable), Token(tMinus), Token(tVariable), Token(tSemi), Token(tEnd)
    };

    PrecedenceParser exprParser(stackos);
    PredictiveParser predParser(stackos);
    predParser.InitSyntaxAnalysis();
    Parser* currentParser = static_cast<Parser*>(&predParser);
    currentParser->SetParserType(Predictive);

    int retCode = 0;

    while (true) {
        try {
            currentParser->Parse(inputTape);

            // Switch back to predictive after successful precedence parsing
            if (currentParser->GetParserType() == Precedence) {
                currentParser = static_cast<Parser*>(&predParser);
                currentParser->SetParserType(Predictive);
                continue;
            }
            else {
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
        catch (SyntaxAnalysisSuccess const& e) {
            std::cout << "Parsing successful." << std::endl;
            retCode = 0;
            break;
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