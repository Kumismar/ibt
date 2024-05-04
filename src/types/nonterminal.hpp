/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-05-02 14:45
 */

#pragma once

#include "stack_item.hpp"

/**
 * @brief An enum representing all nonterminal types.
 */
typedef enum nonterminalType
{
    nProgram,
    nStatementList,
    nStatement,
    nIf2,
    nDeclOrExpr,
    nReturnExp,
    nFunctionDef,
    nParams,
    nParams2,
    nExpression,
    nArgs,
    nArgs2,
    nCodeBlock,
    nStatements,
    nVoluntaryType,
    nType,
    // auxiliary type for handling AST context stack
    nStop
} NonterminalType;

/**
 * @brief A class representing a nonterminal symbol.
 */
class Nonterminal : public Symbol
{
private:
    /**
     * @brief Type of the nonterminal.
     */
    NonterminalType ntType;

public:
    /**
     * @brief Nonterminal constructor using type.
     */
    explicit Nonterminal(NonterminalType t);

    /**
     * @brief Nonterminal copy constructor.
     */
    Nonterminal(const Nonterminal& old);

    /**
     * @brief Nonterminal destructor overriding Symbol destructor.
     */
    ~Nonterminal() override = default;

    /**
     * @brief Nonterminal equality operator.
     * @details Compares two nonterminals by their types.
     * @param other The nonterminal type to compare with.
     * @return True if the types are equal, false otherwise.
     */
    bool operator==(const NonterminalType& other) const;

    /**
     * @brief Nonterminal equality operator.
     * @details Compares two nonterminals by their types.
     * @param other The nonterminal to compare with.
     * @return True if the types are equal, false otherwise.
     */
    bool operator==(const Nonterminal& other) const;

    /**
     * @brief Returns type of the nonterminal.
     * @return The type.
     */
    NonterminalType GetNonterminalType() const;

    /**
     * @brief Returns type of the nonterminal as a string.
     * @return The type as a string.
     */
    std::string GetTypeString() const override;

    /**
     * @brief Clones the nonterminal.
     * @return A new instance of the nonterminal.
     */
    Nonterminal* Clone() const override;
};