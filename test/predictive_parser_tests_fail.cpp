/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-02 12:42
 * @ Modified time: 2024-04-03 17:28
 */

#include <gtest/gtest.h>

#include "predictive.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

class PredictiveParserTestsFail : public ::testing::Test
{
protected:
    AnalysisStack stack;
    PredictiveParser* parser = nullptr;

    void SetUp() override
    {
        this->parser = new PredictiveParser(stack);
        this->parser->InitSyntaxAnalysis();
    }

    void TearDown() override
    {
        this->parser->ClearStack();
        for (auto token: inputTape) {
            delete token;
        }
        inputTape.clear();
        delete this->parser;
    }
};

TEST_F(PredictiveParserTestsFail, EmptyInput)
{
    inputTape = { new Token(tEnd) };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, MissingEndToken)
{
    inputTape = { new Token(tConst), new Token(tSemi) };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionCallMissingClosingParenthesis)
{
    inputTape = {
        new Token(tFuncName), new Token(tLPar), new Token(tConst), new Token(tSemi), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionCallMissingOpeningParenthesis)
{
    inputTape = {
        new Token(tFuncName), new Token(tRPar), new Token(tSemi), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionCallMissingComma)
{
    inputTape = {
        new Token(tFuncName), new Token(tLPar), new Token(tConst), new Token(tConst), new Token(tRPar), new Token(tSemi), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, MissingSemicolon)
{
    inputTape = {
        new Token(tFuncName), new Token(tLPar), new Token(tConst), new Token(tComma), new Token(tConst), new Token(tRPar), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, MissingSemicolonTwoStatements)
{
    inputTape = {
        new Token(tFuncName), new Token(tLPar), new Token(tConst), new Token(tComma), new Token(tConst), new Token(tRPar), new Token(tSemi),
        new Token(tFuncName), new Token(tLPar), new Token(tConst), new Token(tComma), new Token(tConst), new Token(tRPar), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, ForLoopMissingInitialization)
{
    inputTape = {
        new Token(tFor), new Token(tLPar), new Token(tSemi), new Token(tConst), new Token(tSemi), new Token(tConst), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, ForLoopMissingCondition)
{
    inputTape = {
        new Token(tFor), new Token(tLPar), new Token(tConst), new Token(tSemi), new Token(tSemi), new Token(tConst), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, ForLoopMissingIncrement)
{
    inputTape = {
        new Token(tFor), new Token(tLPar), new Token(tConst), new Token(tSemi), new Token(tConst), new Token(tSemi), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, WhileLoopMissingCondition)
{
    inputTape = {
        new Token(tWhile), new Token(tLPar), new Token(tRPar), new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, IfStatementMissingCondition)
{
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tRPar), new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, IfStatementNonsenseCondition)
{
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tReturn), new Token(tConst), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionDefinitionMissingComma)
{
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Token(tInt), new Token(tVariable), new Token(tInt), new Token(tVariable), new Token(tRPar),
        new Token(tColon),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionDefinitionMissingColon)
{
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Token(tInt), new Token(tVariable), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionDefinitionNoFunctionKeyword)
{
    inputTape = {
        new Token(tFuncName), new Token(tLPar), new Token(tInt), new Token(tVariable), new Token(tRPar),
        new Token(tColon),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}