/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-02 14:54
 * @ Modified time: 2024-04-03 17:32
 */

#include <gtest/gtest.h>

#include "nonterminal.hpp"
#include "precedence.hpp"
#include "token.hpp"

class PrecedenceParserTestSuccess : public ::testing::Test
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

TEST_F(PrecedenceParserTestSuccess, SimpleAssign)
{
    inputTape = { new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
    EXPECT_TRUE(this->stack.empty());
}

TEST_F(PrecedenceParserTestSuccess, PlusOperator)
{
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, MinusOperator)
{
    inputTape = { new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, MulOperator)
{
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, DivOperator)
{
    inputTape = { new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ConcatOperator)
{
    inputTape = { new Token(tVariable), new Token(tConcat), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, AndOperator)
{
    // a && b
    inputTape = { new Token(tVariable), new Token(tAnd), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, OrOperator)
{
    // a || b
    inputTape = { new Token(tVariable), new Token(tOr), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTestSuccess, NotOperator)
{
    // !a
    inputTape = { new Token(tExcl), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, UnaryMinusOperator)
{
    // -a
    inputTape = { new Token(tUnMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, AddMulCombination)
{
    // a + b * c
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, SubDivCombination)
{
    // a - b / c
    inputTape = { new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, MulAddCombination)
{
    // a * b + c
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, DivSubCombination)
{
    // a / b - c
    inputTape = { new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, MulDivCombination)
{
    // a * b / c
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTestSuccess, VarInParentheses)
{
    // (a)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, AddInParentheses)
{
    // (a + b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, SubInParentheses)
{
    // (a - b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tMinus), new Token(tConst), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, MulInParentheses)
{
    // (a * b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, DivInParentheses)
{
    // (a / b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ConcatInParentheses)
{
    // (a . b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tConcat), new Token(tConst), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTestSuccess, NestedParentheses1)
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

TEST_F(PrecedenceParserTestSuccess, NestedParentheses2)
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

TEST_F(PrecedenceParserTestSuccess, NestedParentheses3)
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

TEST_F(PrecedenceParserTestSuccess, NestedParentheses4)
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


TEST_F(PrecedenceParserTestSuccess, ParenthesesAndUnary1)
{
    // (a + (-b))
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ParenthesesAndUnary2)
{
    // (-(-a))
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}


TEST_F(PrecedenceParserTestSuccess, ParenthesesUnaryBinary1)
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

TEST_F(PrecedenceParserTestSuccess, ParenthesesUnaryBinary2)
{
    // (-(-a) + b * c)
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ParenthesesUnaryBinary3)
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

TEST_F(PrecedenceParserTestSuccess, ParenthesesUnaryBinary4)
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

TEST_F(PrecedenceParserTestSuccess, FunctionCallNoArgs)
{
    // f()
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallOneArg)
{
    // f(a)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallTwoArgs)
{
    // f(a, b)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallThreeArgs)
{
    // f(a, b, c)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallNested)
{
    // f(a, g(b, c))
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallNested2)
{
    // f(g(a, b), c)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar),
                  new Token(tComma), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallNested3)
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

TEST_F(PrecedenceParserTestSuccess, FunctionCallNested4)
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

TEST_F(PrecedenceParserTestSuccess, FunctionCallNested5)
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

TEST_F(PrecedenceParserTestSuccess, FunctionCallNested6)
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

TEST_F(PrecedenceParserTestSuccess, ExpressionInFunctionCall)
{
    // f(a + b, c * d)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tMul), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ExpressionInFunctionCall2)
{
    // f(a + b * c, d)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ExpressionInFunctionCall3)
{
    // f(a + b * c, d + e)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ExpressionInFunctionCall4)
{
    // f(a + b * c, d + e * f)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, ExpressionInFunctionCall5)
{
    // f(a + b * c, d + e * f + g)
    inputTape = { new Token(tFuncName), new Token(tLPar),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tComma),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tPlus), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallsInExpression)
{
    // a + f(b, c)
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable),
                  new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallsInExpression2)
{
    // a + f(b, c) * d
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallsInExpression3)
{
    // a + f(b, c) * d + e
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallsInExpression4)
{
    // a + f(b, c) * d + e * f(g, h)
    inputTape = { new Token(tVariable), new Token(tPlus),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar), new Token(tMul),
                  new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul),
                  new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tComma), new Token(tVariable), new Token(tRPar),
                  new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser->Parse());
}

TEST_F(PrecedenceParserTestSuccess, FunctionCallsInExpression5)
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

TEST_F(PrecedenceParserTestSuccess, MixedFunctionCallsAndExpressions)
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

TEST_F(PrecedenceParserTestSuccess, NestedFunctionCallsAndExpressions)
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

TEST_F(PrecedenceParserTestSuccess, AssignComplexExpression)
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
