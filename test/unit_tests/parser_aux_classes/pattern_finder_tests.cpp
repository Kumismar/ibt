/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 18:31
 * @ Modified time: 2024-04-30 13:58
 */

#include "ast.hpp"
#include "common.hpp"
#include "internal_error.hpp"
#include "logger.hpp"
#include "nonterminal.hpp"
#include "pattern_finder.hpp"
#include "precedence_symbol.hpp"
#include "token.hpp"
#include <gtest/gtest.h>

class PatternFinderTests : public ::testing::Test
{
protected:
    AnalysisStack stack;
    PatternFinder* finder = nullptr;
    Rule rule;
    Rule expected;

    void SetUp() override
    {
        finder = new PatternFinder(this->stack);
        AST::GetInstance()->TurnOff();
        Logger::GetInstance()->TurnOff();
    }

    void TearDown() override
    {
        delete finder;
        if (!this->stack.empty()) {
            for (auto symb: this->stack) {
                delete symb;
            }
            this->stack.clear();
        }
        AST::Cleanup();
        Logger::Cleanup();
        cleanRule(this->rule);
        cleanRule(this->expected);
    }
};


TEST_F(PatternFinderTests, FindFirstTokenInStackOneToken)
{
    this->stack = {
        new Token(tConst),
    };
    Token* token = finder->FindFirstToken();
    EXPECT_EQ(token->GetTokenType(), tConst);
}

TEST_F(PatternFinderTests, FindFirstTokenInStackMultipleTokens)
{
    this->stack = {
        new Token(tConst),
        new Token(tVariable),
        new Token(tExpEnd),
    };
    Token* token = finder->FindFirstToken();
    EXPECT_EQ(token->GetTokenType(), tConst);
}

TEST_F(PatternFinderTests, FindFirstTokenInStackNoToken)
{
    this->stack = {
        new Nonterminal(nExpression),
        new Nonterminal(nExpression),
        new Nonterminal(nExpression)
    };
    EXPECT_THROW(finder->FindFirstToken(), InternalError);
}

TEST_F(PatternFinderTests, FindFirstTokenInStackTokenBetweenNonterminals)
{
    this->stack = {
        new Nonterminal(nExpression),
        new Token(tConst),
        new Nonterminal(nExpression)
    };
    Token* token = finder->FindFirstToken();
    EXPECT_EQ(token->GetTokenType(), tConst);
}

TEST_F(PatternFinderTests, FindFirstRuleOneConstant)
{
    this->stack = {
        new Token(tConst),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd),
    };

    finder->FindFirstRule(this->rule);
    this->expected = {
        new Token(tConst),
    };
    this->expected.reverse();
    EXPECT_TRUE(handlesEqual(rule, expected));
}

TEST_F(PatternFinderTests, FindFirstRuleMultipleConstants)
{
    this->stack = {
        new Token(tConst),
        new Token(tVariable),
        new Token(tConst),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd),
    };

    finder->FindFirstRule(this->rule);
    this->expected = {
        new Token(tConst),
        new Token(tVariable),
        new Token(tConst),
    };
    this->expected.reverse();
    EXPECT_TRUE(handlesEqual(rule, expected));
}

TEST_F(PatternFinderTests, FindFirstRuleNonterminal)
{
    this->stack = {
        new Nonterminal(nExpression),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd),
    };

    finder->FindFirstRule(this->rule);
    this->expected = {
        new Nonterminal(nExpression),
    };
    this->expected.reverse();
    EXPECT_TRUE(handlesEqual(rule, expected));
}

TEST_F(PatternFinderTests, FindFirstRuleMultipleNonterminals)
{
    this->stack = {
        new Nonterminal(nExpression),
        new Nonterminal(nExpression),
        new Nonterminal(nExpression),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd),
    };

    finder->FindFirstRule(this->rule);
    this->expected = {
        new Nonterminal(nExpression),
        new Nonterminal(nExpression),
        new Nonterminal(nExpression),
    };
    this->expected.reverse();
    EXPECT_TRUE(handlesEqual(rule, expected));
}

TEST_F(PatternFinderTests, FindFirstRuleMixed)
{
    this->stack = {
        new Nonterminal(nExpression),
        new Token(tConst),
        new Nonterminal(nExpression),
        new Token(tVariable),
        new Nonterminal(nExpression),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd),
    };

    finder->FindFirstRule(this->rule);
    this->expected = {
        new Nonterminal(nExpression),
        new Token(tConst),
        new Nonterminal(nExpression),
        new Token(tVariable),
        new Nonterminal(nExpression),
    };
    this->expected.reverse();
    EXPECT_TRUE(handlesEqual(rule, expected));
}

TEST_F(PatternFinderTests, FindFirstRuleMixed2)
{
    this->stack = {
        new Token(tConst),
        new Nonterminal(nExpression),
        new Token(tVariable),
        new Nonterminal(nExpression),
        new Token(tConst),
        new PrecedenceSymbol(Push),
        new Token(tExpEnd),
    };

    finder->FindFirstRule(this->rule);
    this->expected = {
        new Token(tConst),
        new Nonterminal(nExpression),
        new Token(tVariable),
        new Nonterminal(nExpression),
        new Token(tConst),
    };
    this->expected.reverse();
    EXPECT_TRUE(handlesEqual(rule, expected));
}
