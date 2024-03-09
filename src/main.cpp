#include "analysis_success.hpp"
#include "change_parser.hpp"
#include "grammar_1.hpp"
#include "grammar_2.hpp"
#include "grammar_3.hpp"
#include "grammar_4.hpp"
#include "grammar_5.hpp"
#include "grammar_6.hpp"
#include "internal_error.hpp"
#include "lex.yy.h"
#include "lexical_error.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "precedence.hpp"
#include "predictive.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <cstdio>
#include <filesystem>
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

    if (!inputTape.empty()) {
        for (const auto& token: inputTape) {
            delete token;
        }
        inputTape.clear();
    }
}

void lex()
{
    namespace fs = std::filesystem;
    fs::path file(__FILE__);
    fs::path toOpen = file.parent_path().parent_path() / "idk.koubp";

    if ((yyin = fopen(toOpen.c_str(), "r")) == nullptr) {
        throw InternalErrorException("Failed to open input file.\n");
    }
    yylex();
    yylex_destroy();
    inputTape.push_back(new Token(tEnd));
    Logger* logger = Logger::GetInstance();
    logger->PrintTokens();
}

void processArguments(int argc, char** argv)
{
}

int main(int argc, char** argv)
{
    processArguments(argc, argv);

    std::list<StackItem*> stackos;
    try {
        lex();
    }
    catch (LexicalErrorException const& e) {
        std::cerr << "Lexical error: " << e.what() << std::endl;
        Cleanup();
        return 5;
    }
    catch (InternalErrorException const& e) {
        std::cerr << "Internal error: " << e.what() << std::endl;
        Cleanup();
        return 2;
    }

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
        catch (std::exception const& e) {
            std::cerr << "Unknown error: " << e.what() << std::endl;
            retCode = 3;
            break;
        }
        catch (...) {
            std::cerr << "Unknown error." << std::endl;
            retCode = 4;
            break;
        }
    }

    predParser.ClearStack();
    Cleanup();
    return retCode;
}