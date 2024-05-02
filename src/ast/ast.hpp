/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-03 10:26
 * @ Modified time: 2024-05-02 20:24
 */


#pragma once

#include "ast_node.hpp"
#include "statement_list.hpp"
#include <fstream>
#include <stack>

/**
 * @brief The main class for the Abstract Syntax Tree.
 * @details The class is implemented as singleton, the instance is created and accessed through the GetInstance method.
 */
class AST
{
private:
    /**
     * @brief The instance of the AST.
     */
    static AST* instance;

    /**
     * @brief The root of the AST.
     */
    StatementList* root = nullptr;

    /**
     * @brief Stack of context nodes.
     * The nodes are connected with LinkNode method in the ASTNode class.
     */
    std::stack<ASTNode*> nodeContext;

    /**
     * @brief Stack of expression nodes.
     * The nodes are connected when reducing the expression.
     */
    std::stack<Expression*> exprContext;

    /**
     * @brief The output file for the AST.
     */
    std::ofstream* file = nullptr;

    /**
     * @brief A flag indicating that the AST should be printed.
     */
    bool printTreeFlag = false;

    /**
     * @brief A flag indicating whether the AST is turned off.
     */
    bool turnedOff = false;

    /**
     * @brief The constructor of the AST.
     * @details The constructor is private because the class is implemented as a singleton.
     * Creates its root and opens the output file.
     */
    AST();

    /**
     * @brief The destructor of the AST.
     * @details Closes the output file.
     */
    ~AST();

public:
    ASTNode* GetCurrentContext();
    Expression* GetExpressionContext();
    void PopContext();
    void PushContext(ASTNode* node);
    void PopExpressionContext();
    void PushExpressionContext(Expression* exp);
    void SetTreeFlag();
    void PrintTree();
    static AST* GetInstance();
    static void Cleanup();
    void TurnOff();
    bool IsTurnedOff();
};