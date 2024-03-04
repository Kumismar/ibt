#include "lex.hpp"
#include "internal_error.hpp"
#include <cstdio>

InputTape inputTape;

LexicalAnalyzer::LexicalAnalyzer(const char* filename)
{
    this->input = fopen(filename, "r");
    if (this->input == nullptr) {
        throw InternalErrorException("Failed to open file\n");
    }
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    fclose(this->input);
}

void LexicalAnalyzer::Tokenize()
{
    yylex();
}