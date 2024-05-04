/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:29
 * @ Modified time: 2024-05-01 12:40
 */

#pragma once

#include "ast_node.hpp"
#include "nonterminal.hpp"

/**
 * @brief An enumeration for the type of the expression.
 */
typedef enum expressionType
{
    Unary,
    Binary,
} ExpressionType;

/**
 * @brief A class representing an expression in the AST.
 */
class Expression : public ASTNode
{
protected:
    /**
     * @brief The type of the expression.
     */
    ExpressionType expressionType;

public:
    /**
     * @brief A destructor.
     */
    ~Expression() override = default;

    /**
     * @brief Prints the tree to the file.
     * @param file The file to print to.
     * @param id The id of the node.
     * @param parentId The id of the parent node.
     */
    void PrintTree(std::ofstream& file, int& id, int parentId) override = 0;

    /**
     * @brief Processes a token.
     * @details This method is called on current AST context.
     * The AST nodes gradually add information to themselves.
     * @param token The token to process.
     */
    void ProcessToken(Token& token) override = 0;

    /**
     * @brief Links a node to the current context based on type of nonterminal.
     * @param node The node to link.
     * @param nt Nonterminal used to determine if the node will be linked.
     * Is used to dynamically cast the node to the correct type.
     */
    void LinkNode(ASTNode* node, Nonterminal& nt) override = 0;
};