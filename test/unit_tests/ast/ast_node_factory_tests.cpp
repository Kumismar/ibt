/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 18:35
 * @ Modified time: 2024-04-29 11:52
 */

#include "ast.hpp"
#include "ast_node_factory.hpp"
#include "binary_expression.hpp"
#include "constant.hpp"
#include "grammar.hpp"
#include "logger.hpp"
#include "token.hpp"
#include "unary_expression.hpp"
#include "variable.hpp"
#include <cassert>
#include <gtest/gtest.h>

class ASTNodeFactoryTests : public ::testing::Test
{
protected:
    Rule rule;
    ASTNodeFactory* factory;
    Expression* expr = nullptr;

    void SetUp() override
    {
        this->factory = new ASTNodeFactory();
        Logger::GetInstance()->TurnOff();
        this->expr = nullptr;
    }

    void TearDown() override
    {
        delete this->factory;

        if (!this->rule.empty()) {
            for (auto symb: this->rule) {
                delete symb;
            }
        }
        AST::Cleanup();
        Logger::Cleanup();

        if (this->expr != nullptr) {
            delete this->expr;
        }
    }

    Token* sampleToken(TokenType type = tConst, DataType dType = Int, Value value = (Value)(0));
    void createExpressionNodeAndPushOperand(Token* t);
};

Token* ASTNodeFactoryTests::sampleToken(TokenType type, DataType dType, Value value)
{
    Token* token = new Token();
    token->SetTokenType(type);
    token->SetData(dType, value);
    return token;
}

void ASTNodeFactoryTests::createExpressionNodeAndPushOperand(Token* t)
{
    this->rule = {
        t
    };
    this->expr = this->factory->CreateASTNode(rule);
    if (this->expr != nullptr) {
        AST::GetInstance()->PushExpressionContext(expr);
        return;
    }
    EXPECT_TRUE(false);
}

TEST_F(ASTNodeFactoryTests, CreateConstant)
{
    this->rule = {
        this->sampleToken()
    };
    this->expr = this->factory->CreateASTNode(this->rule);
    EXPECT_EQ(typeid(Constant), typeid(*expr));
}

TEST_F(ASTNodeFactoryTests, CreateVariable)
{
    this->rule = {
        this->sampleToken(tVariable)
    };
    this->expr = this->factory->CreateASTNode(this->rule);
    EXPECT_EQ(typeid(Variable), typeid(*expr));
}

TEST_F(ASTNodeFactoryTests, CreateUnaryExpression)
{
    Token* constant = this->sampleToken(tConst);
    this->createExpressionNodeAndPushOperand(constant);

    Token* unMinus = this->sampleToken(tUnMinus);
    this->rule = {
        unMinus,
        constant
    };
    this->expr = this->factory->CreateASTNode(this->rule);
    EXPECT_EQ(typeid(UnaryExpression), typeid(*expr));
}

TEST_F(ASTNodeFactoryTests, CreateBinaryExpression)
{
    Token* constant1 = this->sampleToken(tConst);
    this->createExpressionNodeAndPushOperand(constant1);

    Token* constant2 = this->sampleToken(tConst);
    this->createExpressionNodeAndPushOperand(constant2);

    Token* plus = this->sampleToken(tPlus);
    this->rule = {
        constant1,
        plus,
        constant2
    };
    this->expr = this->factory->CreateASTNode(this->rule);
    EXPECT_EQ(typeid(BinaryExpression), typeid(*expr));
}