/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-02 14:54
 * @ Modified time: 2024-04-02 12:49
 */

#include <gtest/gtest.h>

#include "nonterminal.hpp"
#include "precedence.hpp"
#include "token.hpp"

class PrecedenceParserTest : public ::testing::Test
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
    }
};

TEST_F(PrecedenceParserTest, SingleVariable)
{
    inputTape = { new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
    EXPECT_TRUE(this->stack.empty());
}

TEST_F(PrecedenceParserTest, SimpleAssign)
{
    inputTape = { new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
    EXPECT_TRUE(this->stack.empty());
}

TEST_F(PrecedenceParserTest, PlusOperator)
{
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, MinusOperator)
{
    inputTape = { new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, MulOperator)
{
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, DivOperator)
{
    inputTape = { new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ConcatOperator)
{
    inputTape = { new Token(tVariable), new Token(tConcat), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, AndOperator)
{
    // a && b
    inputTape = { new Token(tVariable), new Token(tAnd), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, OrOperator)
{
    // a || b
    inputTape = { new Token(tVariable), new Token(tOr), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTest, NotOperator)
{
    // !a
    inputTape = { new Token(tExcl), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, UnaryMinusOperator)
{
    // -a
    inputTape = { new Token(tUnMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, AddMulCombination)
{
    // a + b * c
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, SubDivCombination)
{
    // a - b / c
    inputTape = { new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, MulAddCombination)
{
    // a * b + c
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, DivSubCombination)
{
    // a / b - c
    inputTape = { new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, MulDivCombination)
{
    // a * b / c
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTest, VarInParentheses)
{
    // (a)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, AddInParentheses)
{
    // (a + b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, SubInParentheses)
{
    // (a - b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tMinus), new Token(tConst), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, MulInParentheses)
{
    // (a * b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, DivInParentheses)
{
    // (a / b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ConcatInParentheses)
{
    // (a . b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tConcat), new Token(tConst), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTest, NestedParentheses1)
{
    // (a + (b * c))
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tRPar), new Token(tRPar),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, NestedParentheses2)
{
    // (a + (b * c) + d)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tRPar),
        new Token(tPlus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, NestedParentheses3)
{
    // (a + (b * (c + (d * e) + f) + g) + h)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tLPar), new Token(tVariable),
        new Token(tMul), new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tLPar), new Token(tVariable),
        new Token(tMul), new Token(tVariable), new Token(tRPar),
        new Token(tPlus), new Token(tVariable), new Token(tRPar),
        new Token(tPlus), new Token(tVariable), new Token(tRPar),
        new Token(tPlus), new Token(tVariable), new Token(tRPar),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, NestedParentheses4)
{
    // ((((a + b)) * d) + (c * e))
    inputTape = {
        new Token(tLPar), new Token(tLPar), new Token(tLPar), new Token(tLPar),
        new Token(tVariable), new Token(tPlus), new Token(tVariable),
        new Token(tRPar), new Token(tRPar),
        new Token(tMul), new Token(tVariable), new Token(tRPar),
        new Token(tPlus), new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tRPar), new Token(tRPar),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTest, ParenthesesAndUnary1)
{
    // (a + (-b))
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ParenthesesAndUnary2)
{
    // (-(-a))
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTest, ParenthesesUnaryBinary1)
{
    // (a + (-b) * c)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tMul), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ParenthesesUnaryBinary2)
{
    // (-(-a) + b * c)
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ParenthesesUnaryBinary3)
{
    // (a + (-b) * c + d)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tMul), new Token(tVariable),
        new Token(tPlus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ParenthesesUnaryBinary4)
{
    // (-(-a) + b * c + d)
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tPlus), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNoArgs)
{
    // f()
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallOneArg)
{
    // f(a)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallTwoArgs)
{
    // f(a, b)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallThreeArgs)
{
    // f(a, b, c)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNested)
{
    // f(a, g(b, c))
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNested2)
{
    // f(g(a, b), c)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tComma), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNested3)
{
    // f(g(a, b), h(c, d))
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNested4)
{
    // f(g(a, h(b, c)), d)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tComma), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNested5)
{
    // f(g(a, h(b, c)), i(d, e))
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallNested6)
{
    // f(g(a, h(b, c)), i(d, e, f))
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ExpressionInFunctionCall)
{
    // f(a + b, c * d)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tMul), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ExpressionInFunctionCall2)
{
    // f(a + b * c, d)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ExpressionInFunctionCall3)
{
    // f(a + b * c, d + e)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ExpressionInFunctionCall4)
{
    // f(a + b * c, d + e * f)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, ExpressionInFunctionCall5)
{
    // f(a + b * c, d + e * f + g)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tPlus), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallsInExpression)
{
    // a + f(b, c)
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallsInExpression2)
{
    // a + f(b, c) * d
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallsInExpression3)
{
    // a + f(b, c) * d + e
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallsInExpression4)
{
    // a + f(b, c) * d + e * f(g, h)
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, FunctionCallsInExpression5)
{
    // a + f(b, c) * d + e * f(g, h) + i(j, k)
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, MixedFunctionCallsAndExpressions)
{
    // f(a + b, c * d) + e * f(g, h) + i(j, k)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tMul), new Token(tVariable),
                  new Token(tRPar), new Token(tPlus),
                  new Token(tVariable), new Token(tMul),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, NestedFunctionCallsAndExpressions)
{
    // f(a + f(b(c + 1), c(g(3) * 5)), d * f(g, h))
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tConst),
                  new Token(tRPar), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tConst),
                  new Token(tRPar), new Token(tMul), new Token(tConst),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tComma), new Token(tVariable), new Token(tMul),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTest, AssignComplexExpression)
{
    // a = ((b = f(i + 2)) != 0)
    inputTape = { new Token(tVariable), new Token(tAssign), new Token(tLPar),
                  new Token(tLPar), new Token(tVariable), new Token(tAssign),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tConst), new Token(tRPar),
                  new Token(tRPar), new Token(tNEq), new Token(tConst),
                  new Token(tRPar),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}
