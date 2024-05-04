/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 11:22
 * @ Modified time: 2024-05-01 12:20
 */

#pragma once

#include "expression.hpp"
#include "operator.hpp"
#include "token.hpp"

/**
 * @brief A class representing a binary expression in the AST.
 */
class BinaryExpression : public Expression
{
private:
    /**
     * @brief Left operand of the binary expression.
     */
    Expression* left = nullptr;

    /**
     * @brief Operator of the binary expression.
     */
    Operator* optr = nullptr;

    /**
     * @brief Right operand of the binary expression.
     */
    Expression* right = nullptr;

public:
    /**
     * @brief Create BinaryExpression and set expression type.
     * @param t Token type of the operator.
     */
    explicit BinaryExpression(TokenType t);

    /**
     * @brief A destructor.
     */
    ~BinaryExpression() override;

    /**
     * @brief Get the left operand of the binary expression.
     * @return The left operand of the binary expression.
     */
    Expression* GetLeft() const;

    /**
     * @brief Get the operator of the binary expression.
     * @return The operator of the binary expression.
     */
    Expression* GetRight() const;

    /**
     * @brief Print the tree of the binary expression.
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