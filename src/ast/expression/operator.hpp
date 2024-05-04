/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:25
 * @ Modified time: 2024-04-16 13:08
 */

#pragma once

#include "token.hpp"

/**
 * @brief An enumeration for the type of the operator.
 */
typedef enum operatorType
{
    Plus,
    Minus,
    Multiply,
    Divide,
    Concat,
    Assign,
    Equal_ot,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    And,
    Or,
    Not,
    UnaryMinus,
    ExpInParentheses
} OperatorType;

/**
 * @brief A class representing an operator in the AST.
 */
class Operator
{
private:
    /**
     * @brief Type of the operator.
     */
    OperatorType type;

public:
    /**
     * @brief A constructor.
     * @param t The token type of the operator.
     */
    explicit Operator(TokenType t);

    /**
     * @brief Get the operator type.
     * @return The operator type.
     */
    OperatorType GetType() const;

    /**
     * @brief Get the operator precedence.
     * @return The operator precedence.
     */
    void PrintTree(std::ofstream& file, int& id, int parentId);
};