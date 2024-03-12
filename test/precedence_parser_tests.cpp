#include <gtest/gtest.h>

#include "change_parser.hpp"
#include "nonterminal.hpp"
#include "precedence.hpp"
#include "token.hpp"

class PrecedenceParserTest : public ::testing::Test
{
protected:
    std::list<StackItem*> stack;
    PrecedenceParser parser = PrecedenceParser(this->stack);
};

TEST_F(PrecedenceParserTest, SingleVariable)
{
    this->stack.push_front(new Nonterminal(nExpression));
    inputTape = { new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
    EXPECT_TRUE(this->stack.empty());
}

TEST_F(PrecedenceParserTest, SimpleAssign)
{
    this->stack.push_front(new Nonterminal(nExpression));
    inputTape = { new Token(tVariable), new Token(tAssign), new Token(tConst), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
    EXPECT_TRUE(this->stack.empty());
}

TEST_F(PrecedenceParserTest, SimpleArithmeticOperators)
{
    // a + b
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a - b
    inputTape = { new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a * b
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a / b
    inputTape = { new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a . b
    inputTape = { new Token(tVariable), new Token(tConcat), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, SimpleLogicalOperators)
{
    // a && b
    inputTape = { new Token(tVariable), new Token(tAnd), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a || b
    inputTape = { new Token(tVariable), new Token(tOr), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, SimpleUnaryOperators)
{
    // !a
    inputTape = { new Token(tExcl), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // -a
    inputTape = { new Token(tUnMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, CombinedAritmeticOperators)
{
    // a + b * c
    inputTape = { new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a - b / c
    inputTape = { new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a * b + c
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a / b - c
    inputTape = { new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tMinus), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // a * b / c
    inputTape = { new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, SimpleParentheses)
{
    // (a)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a + b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tPlus), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a - b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tMinus), new Token(tConst), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a * b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a / b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tDiv), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a . b)
    inputTape = { new Token(tLPar), new Token(tVariable), new Token(tConcat), new Token(tConst), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, NestedParentheses)
{
    // (a + (b * c))
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tRPar), new Token(tRPar),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a + (b * c) + d)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tLPar), new Token(tVariable), new Token(tMul), new Token(tVariable), new Token(tRPar),
        new Token(tPlus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());

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
    EXPECT_NO_THROW(this->parser.Parse());

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
}

TEST_F(PrecedenceParserTest, ParenthesesAndUnary)
{
    // (a + (-b))
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());

    // (-(-a))
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, ParenthesesUnaryBinary)
{
    // (a + (-b) * c)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tMul), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());

    // (-(-a) + b * c)
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());

    // (a + (-b) * c + d)
    inputTape = {
        new Token(tLPar), new Token(tVariable),
        new Token(tPlus), new Token(tUnMinus), new Token(tVariable),
        new Token(tMul), new Token(tVariable),
        new Token(tPlus), new Token(tVariable),
        new Token(tRPar), new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());

    // (-(-a) + b * c + d)
    inputTape = {
        new Token(tUnMinus), new Token(tUnMinus), new Token(tVariable),
        new Token(tPlus), new Token(tVariable), new Token(tMul), new Token(tVariable),
        new Token(tPlus), new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse());
}

TEST_F(PrecedenceParserTest, FunctionCall)
{
    // f(a)
    inputTape = { new Token(tFuncName), new Token(tLPar), new Token(tVariable), new Token(tRPar), new Token(tExpEnd) };
    EXPECT_THROW(this->parser.Parse(), ChangeParser);
}