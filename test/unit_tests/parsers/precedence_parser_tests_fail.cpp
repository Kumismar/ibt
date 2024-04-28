/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 17:28
 * @ Modified time: 2024-04-15 14:49
 */

#include <gtest/gtest.h>

#include "ast.hpp"
#include "nonterminal.hpp"
#include "precedence_parser.hpp"
#include "syntax_error.hpp"
#include "token.hpp"

class PrecedenceParserTestsFail : public ::testing::Test
{
protected:
    AnalysisStack stack;
    PrecedenceParser* parser = nullptr;

    void SetUp() override
    {
        this->parser = new PrecedenceParser(this->stack);
        this->stack.push_front(new Nonterminal(nExpression));
    }

    void TearDown() override
    {
        for (auto token: inputTape) {
            delete token;
        }
        inputTape.clear();
        delete this->parser;
        AST::GetInstance()->Cleanup();
    }
};

TEST_F(PrecedenceParserTestsFail, EmptyInput)
{
    inputTape = { new Token(tEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, UnexpectedTokenInExpression)
{
    // a + ; b
    inputTape = { new Token(tConst), new Token(tPlus), new Token(tSemi), new Token(tConst), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, InvalidFunctionCallSyntax)
{
    // f(a + b,)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tComma), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, InvalidExpressionWithinParentheses)
{
    // (a + b +)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tPlus), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, ConsecutiveOperators)
{
    // a + + b
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, MissingOperand)
{
    // a +
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, InvalidUnaryOperator)
{
    // * a
    inputTape = { new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, UnmatchedParentheses)
{
    // (a + b
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}

TEST_F(PrecedenceParserTestsFail, MissingOperatorInParentheses)
{
    // (a b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_THROW(this->parser->Parse(), SyntaxError);
}
