/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-23 19:09
 * @ Modified time: 2024-03-30 13:21
 */

#include <gtest/gtest.h>

#include "analysis_success.hpp"
#include "predictive.hpp"
#include "syntax_error.hpp"
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

TEST_F(PredictiveParserTests, EmptyInput)
{
    inputTape = { new Token(tEnd) };
    EXPECT_THROW(this->parser.Parse(false), SyntaxError);
}

TEST_F(PredictiveParserTests, VariableAssignment)
{
    inputTape = {
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, IfStatementEmpty)
{
    // if (const) { }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, IfStatement)
{
    // if (const) { variable = const; }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, IfElseStatement)
{
    // if (const) { variable = const; } else { variable = const; }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl),
        new Token(tElse),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, IfElseifStatement)
{
    // if (const) { variable = const; } elseif (const) { variable = const; }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl),
        new Token(tElseif), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, IfElseIfElseStatement)
{
    // if (const) { variable = const; } elseif (const) { variable = const; } else { variable = const; }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl),
        new Token(tElseif), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl),
        new Token(tElse),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, IfStatementNoBraces)
{
    // if (const) variable = const;
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, WhileLoop)
{
    // while (const) { variable = const; }
    inputTape = {
        new Token(tWhile), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, WhileLoopNoBraces)
{
    // while (const) variable = const;
    inputTape = {
        new Token(tWhile), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, ForLoop)
{
    // for (variable = const; const; const) { variable = const; }
    inputTape = {
        new Token(tFor), new Token(tLPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tConst), new Token(tSemi),
        new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, ForLoopNoBraces)
{
    // for (variable = const; const; const) variable = const;
    inputTape = {
        new Token(tFor), new Token(tLPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tConst), new Token(tSemi),
        new Token(tConst), new Token(tRPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, ReturnStatement)
{
    // return const;
    inputTape = {
        new Token(tReturn), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, ReturnStatementNoValue)
{
    // return;
    inputTape = {
        new Token(tReturn), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, Expression)
{
    // 3 + 4 * 5;
    inputTape = {
        new Token(tConst), new Token(tPlus), new Token(tConst), new Token(tMul), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
}

TEST_F(PredictiveParserTests, CodeBlock)
{
    // { variable = const; }
    inputTape = {
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, CodeBlockEmpty)
{
    // { }
    inputTape = {
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, FunctionDefinitionNoTypeNoArgs)
{
    // function f(): { return; }
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Token(tRPar), new Token(tColon),
        new Token(tLCurl),
        new Token(tReturn), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, FunctionDefinitionNoTypeOneArg)
{
    // function f(int variable): { return variable; }
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar),
        new Token(tInt), new Token(tVariable), new Token(tRPar), new Token(tColon),
        new Token(tLCurl),
        new Token(tReturn), new Token(tVariable), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, FunctionDefinitionNoTypeTwoArgs)
{
    // function f(int variable, int variable2): { return variable + variable2; }
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar),
        new Token(tInt), new Token(tVariable), new Token(tComma),
        new Token(tInt), new Token(tVariable), new Token(tRPar), new Token(tColon), new Token(tInt),
        new Token(tLCurl),
        new Token(tReturn), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTests, FunctionDefinitionIntNoArgs)
{
    // function f(): int { return; }
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Token(tRPar), new Token(tColon),
        new Token(tInt),
        new Token(tLCurl),
        new Token(tReturn), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
}

TEST_F(PredictiveParserTests, StatementSequence)
{
    // variable = const; variable = const;
    inputTape = {
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser.Parse(false), SyntaxAnalysisSuccess);
}
