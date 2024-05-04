/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:26
 * @ Modified time: 2024-05-01 12:10
 */

#pragma once

#include "expression.hpp"
#include "operand.hpp"
#include "operator.hpp"

/**
 * @brief A class representing a unary expression in the AST.
 */
class UnaryExpression : public Expression
{
private:
    /**
     * @brief An operator of the unary expression.
     */
    Operator* optr = nullptr;

    /**
     * @brief An operand of the unary expression.
     */
    Expression* operand = nullptr;

public:
    /**
     * @brief Create UnaryExpression and set node type.
     * @param t Token type of the operator.
     */
    UnaryExpression(TokenType t);

    /**
     * @brief A destructor.
     */
    ~UnaryExpression() override;

    /**
     * @brief Get the operator of the unary expression.
     * @return The operator of the unary expression.
     */
    Operator* GetOperator() const;

    /**
     * @brief Get the operand of the unary expression.
     * @return The operand of the unary expression.
     */
    Expression* GetOperand() const;

    /**
     * @brief Print the tree of the unary expression.
     * @param file File to write to.
     * @param id ID of the node.
     * @param parentId ID of the parent node.
     */
    void PrintTree(std::ofstream& file, int& id, int parentId) override;

    /**
     * @brief Processes a token.
     * @details This method is called on current AST context.
     * The AST nodes gradually add information to themselves.
     * @param token The token to process.
     */
    void ProcessToken(Token& token) override;

    /**
     * @brief Link a node to the AST.
     * @details This method is called on current AST context.
     * The AST nodes are linked to each other.
     * @param node The node to link.
     * @param nt Nonterminal used to determine if the node will be linked.
     * Is used to dynamically cast the node to the correct type.
     */
    void LinkNode(ASTNode* node, Nonterminal& nt) override;
};