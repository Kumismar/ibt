#include <gtest/gtest.h>
#include <stack>

#include "precedence.hpp"
#include "token.hpp"

class PrecedenceParserTest : public ::testing::Test
{
protected:
    std::stack<StackItem*> stack;
    PrecedenceParser parser = PrecedenceParser(this->stack);
    std::list<Token> inputTape;
};

TEST_F(PrecedenceParserTest, SingleVariable)
{
    this->inputTape = { Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, SimpleAssign)
{
    this->inputTape = { Token(tVariable), Token(tAssign), Token(tConst), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, SimpleArithmeticOperators)
{
    this->inputTape = { Token(tVariable), Token(tPlus), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tMinus), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tMul), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tDiv), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tConcat), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, SimpleLogicalOperators)
{
    this->inputTape = { Token(tVariable), Token(tAnd), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tOr), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, SimpleUnaryOperators)
{
    this->inputTape = { Token(tExcl), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tMinus), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, CombinedAritmeticOperators)
{
    this->inputTape = { Token(tVariable), Token(tPlus), Token(tVariable), Token(tMul), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tMinus), Token(tVariable), Token(tDiv), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tMul), Token(tVariable), Token(tPlus), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tDiv), Token(tVariable), Token(tMinus), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tVariable), Token(tMul), Token(tVariable), Token(tDiv), Token(tVariable), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, SimpleParentheses)
{
    this->inputTape = { Token(tLPar), Token(tVariable), Token(tRPar), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tLPar), Token(tVariable), Token(tPlus), Token(tVariable), Token(tRPar), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tLPar), Token(tVariable), Token(tMinus), Token(tConst), Token(tRPar), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tLPar), Token(tVariable), Token(tMul), Token(tVariable), Token(tRPar), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tLPar), Token(tVariable), Token(tDiv), Token(tVariable), Token(tRPar), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    this->inputTape = { Token(tLPar), Token(tVariable), Token(tConcat), Token(tConst), Token(tRPar), Token(tExpEnd) };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}

TEST_F(PrecedenceParserTest, NestedParentheses)
{
    // (a + (b * c))
    this->inputTape = {
        Token(tLPar), Token(tVariable),
        Token(tPlus), Token(tLPar), Token(tVariable), Token(tMul), Token(tVariable),
        Token(tRPar), Token(tRPar),
        Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    // (a + (b * c) + d)
    this->inputTape = {
        Token(tLPar), Token(tVariable),
        Token(tPlus), Token(tLPar), Token(tVariable), Token(tMul), Token(tVariable), Token(tRPar),
        Token(tPlus), Token(tVariable),
        Token(tRPar), Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    // (a + (b * (c + (d * e) + f) + g) + h)
    this->inputTape = {
        Token(tLPar), Token(tVariable),
        Token(tPlus), Token(tLPar), Token(tVariable),
        Token(tMul), Token(tLPar), Token(tVariable),
        Token(tPlus), Token(tLPar), Token(tVariable),
        Token(tMul), Token(tVariable), Token(tRPar),
        Token(tPlus), Token(tVariable), Token(tRPar),
        Token(tPlus), Token(tVariable), Token(tRPar),
        Token(tPlus), Token(tVariable), Token(tRPar),
        Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    // two operations in lots of parentheses
    // ((((a + b)) * d) + (c * e))
    this->inputTape = {
        Token(tLPar), Token(tLPar), Token(tLPar), Token(tLPar),
        Token(tVariable), Token(tPlus), Token(tVariable),
        Token(tRPar), Token(tRPar),
        Token(tMul), Token(tVariable), Token(tRPar),
        Token(tPlus), Token(tLPar), Token(tVariable), Token(tMul), Token(tVariable),
        Token(tRPar), Token(tRPar),
        Token(tExpEnd)
    };
}

TEST_F(PrecedenceParserTest, ParenthesesAndUnary)
{
    // (a + (-b))
    this->inputTape = {
        Token(tLPar), Token(tVariable),
        Token(tPlus), Token(tMinus), Token(tVariable),
        Token(tRPar), Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));

    // (-(-a))
    this->inputTape = {
        Token(tMinus), Token(tMinus), Token(tVariable),
        Token(tExpEnd)
    };
    EXPECT_NO_THROW(this->parser.Parse(this->inputTape));
}
