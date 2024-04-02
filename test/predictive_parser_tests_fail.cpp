/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-02 12:42
 * @ Modified time: 2024-04-02 15:26
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
    inputTape = { new Token(tConst) };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTestsFail, FunctionCallMissingClosingParenthesis)
{
    inputTape = {
        new Token(tFuncName), new Token(tLPar), new Token(tConst), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxError);
}