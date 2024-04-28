/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-23 19:09
 * @ Modified time: 2024-04-15 14:48
 */

#include <gtest/gtest.h>

#include "analysis_success.hpp"
#include "ast.hpp"
#include "predictive_parser.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

class PredictiveParserTestsSuccess : public ::testing::Test
{
protected:
    AnalysisStack stack;
    PredictiveParser* parser = nullptr;

    void SetUp() override
    {
        this->parser = new PredictiveParser(this->stack);
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
        AST::GetInstance()->Cleanup();
    }
};

TEST_F(PredictiveParserTestsSuccess, VariableAssignment)
{
    inputTape = {
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, IfStatementEmpty)
{
    // if (const) { }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, IfStatement)
{
    // if (const) { variable = const; }
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, IfElseStatement)
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
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, IfElseifStatement)
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
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, IfElseIfElseStatement)
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
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, IfStatementNoBraces)
{
    // if (const) variable = const;
    inputTape = {
        new Token(tIf), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, WhileLoop)
{
    // while (const) { variable = const; }
    inputTape = {
        new Token(tWhile), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, WhileLoopNoBraces)
{
    // while (const) variable = const;
    inputTape = {
        new Token(tWhile), new Token(tLPar), new Token(tConst), new Token(tRPar),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, ForLoop)
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
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, ForLoopNoBraces)
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
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, ReturnStatement)
{
    // return const;
    inputTape = {
        new Token(tReturn), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, ReturnStatementNoValue)
{
    // return;
    inputTape = {
        new Token(tReturn), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, Expression)
{
    // 3 + 4 * 5;
    inputTape = {
        new Token(tConst), new Token(tPlus), new Token(tConst), new Token(tMul), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
}

TEST_F(PredictiveParserTestsSuccess, CodeBlock)
{
    // { variable = const; }
    inputTape = {
        new Token(tLCurl),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, CodeBlockEmpty)
{
    // { }
    inputTape = {
        new Token(tLCurl), new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, FunctionDefinitionNoTypeNoArgs)
{
    // function f(): { return; }
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar), new Token(tRPar), new Token(tColon),
        new Token(tLCurl),
        new Token(tReturn), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, FunctionDefinitionNoTypeOneArg)
{
    // function f(int variable): { return variable; }
    inputTape = {
        new Token(tFunction), new Token(tFuncName), new Token(tLPar),
        new Token(tInt), new Token(tVariable), new Token(tRPar), new Token(tColon),
        new Token(tLCurl),
        new Token(tReturn), new Token(tVariable), new Token(tSemi),
        new Token(tRCurl), new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, FunctionDefinitionNoTypeTwoArgs)
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
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}

TEST_F(PredictiveParserTestsSuccess, FunctionDefinitionIntNoArgs)
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

TEST_F(PredictiveParserTestsSuccess, StatementSequence)
{
    // variable = const; variable = const;
    inputTape = {
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tSemi),
        new Token(tEnd)
    };
    EXPECT_THROW(this->parser->Parse(false), SyntaxAnalysisSuccess);
}
