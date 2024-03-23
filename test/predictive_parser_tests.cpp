/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-23 19:09
 * @ Modified time: 2024-03-23 19:19
 */

#include <gtest/gtest.h>

#include "analysis_success.hpp"
#include "predictive.hpp"
#include "token.hpp"

class PredictiveParserTests : public ::testing::Test
{
protected:
    AnalysisStack stack;
    PredictiveParser parser = PredictiveParser(this->stack);

    void SetUp() override
    {
        this->parser.InitSyntaxAnalysis();
    }

    void TearDown() override
    {
        this->parser.ClearStack();
        for (auto token: inputTape) {
            delete token;
        }
        inputTape.clear();
    }
};

TEST_F(PredictiveParserTests, IfStatementEmpty)
{
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}