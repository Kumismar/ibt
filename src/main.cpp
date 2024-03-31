/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-03-31 10:43
 */

#include "analysis_success.hpp"
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
#include "predictive.hpp"
#include "syntax_error.hpp"
#include "token.hpp"
#include <cstdio>
#include <filesystem>
#include <iostream>


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

void Lex(std::string& filename)
{
    namespace fs = std::filesystem;

    fs::path toOpen(filename);
    if (!fs::exists(toOpen)) {
        throw InternalError("Input file not found.\n");
    }

    if ((yyin = fopen(toOpen.c_str(), "r")) == nullptr) {
        throw InternalError("Failed to open input file.\n");
    }
    yylex();
    yylex_destroy();
    inputTape.push_back(new Token(tEnd));
    Logger* logger = Logger::GetInstance();
    logger->PrintTokens();
}

std::string GetFileName(int argc, char** argv)
{
    if (argc != 2) {
        throw InternalError("Invalid number of arguments.\n");
    }
    return std::string(argv[1]);
}

int main(int argc, char** argv)
{
    AnalysisStack stackos;

    try {
        std::string filename = GetFileName(argc, argv);
        Lex(filename);
    }
    catch (LexicalError const& e) {
        std::cerr << "Lexical error: " << e.what() << std::endl;
        Cleanup();
        return 2;
    }
    catch (InternalError const& e) {
        std::cerr << "Internal error: " << e.what() << std::endl;
        Cleanup();
        return 99;
    }

    PredictiveParser* predParser = new PredictiveParser(stackos);
    predParser->InitSyntaxAnalysis();

    int retCode = 0;

    try {
        predParser->Parse(false);
    }
    catch (SyntaxAnalysisSuccess const& e) {
        std::cout << "Parsing successful." << std::endl;
        retCode = 0;
    }
    catch (SyntaxError const& e) {
        Logger::GetInstance()->PrintSyntaxError(e.what());
        retCode = 1;
    }
    catch (InternalError const& e) {
        std::cerr << "Internal error: " << e.what() << std::endl;
        retCode = 99;
    }
    catch (std::exception const& e) {
        std::cerr << "Unknown error: " << e.what() << std::endl;
        retCode = -1;
    }
    catch (...) {
        std::cerr << "Unknown error." << std::endl;
        retCode = -1;
    }

    predParser->ClearStack();
    delete predParser;
    Cleanup();
    return retCode;
}