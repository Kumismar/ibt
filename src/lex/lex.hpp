#include "aux.hpp"
#include "token.hpp"
#include <FlexLexer.h>
#include <cstdio>
#include <string>

class LexicalAnalyzer : public yyFlexLexer
{
private:
    FILE* input;
    std::string lexeme;

public:
    LexicalAnalyzer()
    {
    }

    LexicalAnalyzer(const char* filename);
    ~LexicalAnalyzer();

    void Tokenize();
};

extern InputTape inputTape;