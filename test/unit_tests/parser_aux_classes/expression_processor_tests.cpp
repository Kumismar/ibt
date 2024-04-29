/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 21:48
 * @ Modified time: 2024-04-29 12:48
 */

#include "ast.hpp"
#include "common.hpp"
#include "expression_processor.hpp"
#include "logger.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
#include "token.hpp"
#include <gtest/gtest.h>


class ExpressionProcessorTests : public ::testing::Test
{
protected:
    ExpressionProcessor* processor = nullptr;
    AnalysisStack stack;
    Rule expected;

    void SetUp() override
    {
        this->processor = new ExpressionProcessor(this->stack);
        this->stack = {
            new Token(tExpEnd)
        };
        Logger::GetInstance()->TurnOff();
        AST::GetInstance()->TurnOff();
    }

    void TearDown() override
    {
        if (!inputTape.empty()) {
            for (auto token: inputTape) {
                delete token;
            }
            inputTape.clear();
        }

        cleanRule(this->stack);
        cleanRule(this->expected);

        AST::Cleanup();
        Logger::Cleanup();
        delete this->processor;
    }
};

TEST_F(ExpressionProcessorTests, ShiftTest1)
{
    inputTape = {
        new Token(tConst),
    };
    this->processor->Shift();
    this->expected = {
        new Token(tConst),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, ShiftTest2)
{
    inputTape = {
        new Token(tConst),
        new Token(tPlus),
        new Token(tConst),
    };
    this->processor->Shift();
    this->expected = {
        new Token(tConst),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, ShiftTest3)
{
    inputTape = {
        new Token(tConst),
        new Token(tPlus),
        new Token(tConst),
        new Token(tPlus),
        new Token(tConst),
    };
    this->processor->Shift();
    this->expected = {
        new Token(tConst),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, PushTest1)
{
    inputTape = {
        new Token(tPlus),
        new Token(tConst),
    };
    this->processor->Push();
    this->expected = {
        new Token(tPlus),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, PushTest2)
{
    inputTape = {
        new Token(tVariable),
        new Token(tConst),
        new Token(tPlus),
        new Token(tConst),
    };
    this->processor->Push();
    this->expected = {
        new Token(tVariable),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, PushTest3)
{
    inputTape = {
        new Token(tConst),
        new Token(tConst),
        new Token(tPlus),
        new Token(tConst),
        new Token(tPlus),
        new Token(tConst),
    };
    this->processor->Push();
    this->expected = {
        new Token(tConst),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, ReduceTest1)
{
    Symbol* tmp = this->stack.front();
    this->stack.pop_front();
    this->stack = {
        new Token(tConst),
        new PrecedenceSymbol(Push),
    };
    this->stack.push_back(tmp);
    this->processor->Reduce();
    this->expected = {
        new Nonterminal(nExpression),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, ReduceTest2)
{
    Symbol* tmp = this->stack.front();
    this->stack.pop_front();
    this->stack = {
        new Nonterminal(nExpression),
        new Token(tPlus),
        new Nonterminal(nExpression),
        new PrecedenceSymbol(Push),
    };
    this->stack.push_back(tmp);
    this->processor->Reduce();
    this->expected = {
        new Nonterminal(nExpression),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, ReduceTest3)
{
    Symbol* tmp = this->stack.front();
    this->stack.pop_front();
    this->stack = {
        new Nonterminal(nExpression),
        new Token(tUnMinus),
        new PrecedenceSymbol(Push),
    };
    this->stack.push_back(tmp);

    this->processor->Reduce();
    this->expected = {
        new Nonterminal(nExpression),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}

TEST_F(ExpressionProcessorTests, ReduceTest4)
{
    Symbol* tmp = this->stack.front();
    this->stack.pop_front();
    this->stack = {
        new Token(tFuncConst),
        new PrecedenceSymbol(Push),
    };
    this->stack.push_back(tmp);
    this->processor->Reduce();
    this->expected = {
        new Nonterminal(nExpression),
        new Token(tExpEnd)
    };
    EXPECT_TRUE(handlesEqual(this->expected, this->stack));
}