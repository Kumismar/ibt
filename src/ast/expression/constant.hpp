/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 18:14
 * @ Modified time: 2024-04-16 13:56
 */

#pragma once

#include "operand.hpp"
#include "token.hpp"

/**
 * @brief A class representing a constant in the AST.
 */
class Constant : public Operand
{
public:
    /**
     * @brief Create Constant and set node type.
     * @param t Token of the constant.
     */
    explicit Constant(Token& t);

    /**
     * @brief A destructor.
     */
    ~Constant() override;

    /**
     * @brief Print the tree of the constant.
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