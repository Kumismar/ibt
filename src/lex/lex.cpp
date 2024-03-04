#include "lex.hpp"
#include "internal_error.hpp"
#include <fstream>

LexicalAnalyzer::LexicalAnalyzer(std::string filename)
{
    if (!filename.empty()) {
        std::ifstream* tmp = new std::ifstream(filename);
        if (!tmp->is_open()) {
            delete tmp;
            throw InternalErrorException("File not found (Lex ifstream not open)\n");
        }
        this->input = tmp;
    }
    else {
        this->input = &std::cin;
    }
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    if (this->input != nullptr && this->input != &std::cin) {
        delete this->input;
    }
}

InputTape* LexicalAnalyzer::Tokenize()
{
    return nullptr;
}