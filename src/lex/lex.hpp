#include "aux.hpp"
#include <iostream>
#include <istream>
#include <string>

class LexicalAnalyzer
{
private:
    std::istream* input = nullptr;
    std::string lexeme;

public:
    LexicalAnalyzer(std::string filename);
    ~LexicalAnalyzer();

    InputTape* Tokenize();
};