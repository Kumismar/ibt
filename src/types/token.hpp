/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-22 22:14
 * @ Modified time: 2024-05-02 14:44
 */

#pragma once

#include "stack_item.hpp"
#include <list>
#include <string>

/**
 * @brief An enum representing all possible token types.
 */
typedef enum tokenType
{
    tIf,
    tWhile,
    tFor,
    tReturn,
    tSemi,
    tElseif,
    tElse,
    tLPar,
    tRPar,
    tFunction,
    tFuncName,
    tVariable,
    tComma,
    tColon,
    tPlus,
    tUnMinus,
    tMinus,
    tMul,
    tDiv,
    tConcat,
    tAnd,
    tOr,
    tEq,
    tNEq,
    tGreater,
    tLess,
    tGEq,
    tLEq,
    tExcl,
    tAssign,
    tConst,
    tInt,
    tFloat,
    tString,
    tBool,
    tLCurl,
    tRCurl,
    // Three auxiliary tokens used as stop
    tEnd,
    tExpEnd,
    tFuncEnd,
    // Auxiliary token used to indicate end of function
    tFuncConst,
    tEps
} TokenType;

/**
 * @brief An enum representing all data types in Koubp language.
 */
typedef enum dataType
{
    Int,
    Float,
    String,
    Bool,
    None
} DataType;

/**
 * @brief A union containing token data.
 */
typedef union value
{
    int intVal;
    float floatVal;
    std::string* stringVal = nullptr;
    bool boolVal;
} Value;

/**
 * @brief Data structure for token data consisting of value and type.
 */
typedef struct data {
    DataType type;
    Value value;
} TokenData;

/**
 * @brief A class representing terminal symbols from Koubp grammar system.
 * @details This class works with data and type of the terminal symbol.
 */
class Token : public Symbol
{
private:
    /**
     * @brief Terminal symbol type from Koubp grammar system.
     */
    TokenType type;

    /**
     * @brief Data of the token.
     */
    TokenData data;

    /**
     * @brief Line number on which the corresponding lexeme was found.
     */
    unsigned int lineno;

public:
    // TODO: Remove this constructor and all the refactor all the usages to type constructor
    Token();

    /**
     * @brief Token copy constructor.
     */
    Token(const Token& old);

    /**
     * @brief Token constructor that sets its type without data.
     */
    Token(const TokenType type);

    /**
     * @brief Token destructor overriding Symbol destructor. Safely deletes token data.
     */
    ~Token() override;

    /**
     * @brief Token equality operator.
     * @details Compares two tokens by their types.
     *
     * @param other The token to compare with.
     * @return True if the types are equal, false otherwise.
     */
    bool operator==(const Token& other) const;

    /**
     * @brief Token inequality operator.
     * @details Compares two tokens by their types.
     *
     * @param other The token to compare with.
     * @return True if the types are not equal, false otherwise.
     */
    bool operator!=(const Token& other) const;

    /**
     * @brief Compares token type with type given as argument.
     * 
     * @param other Type to compare with. 
     * @return True if types are equal, false otherwise.
     */
    bool operator==(const TokenType& other) const;

    /**
     * @brief Compares token type with type given as argument.
     * @details Just negates overloaded operator==.
     *
     * @param other Type to compare with. 
     * @return True if types are not equal, false otherwise.
     */
    bool operator!=(const TokenType& other) const;

    /**
     * @brief Returns token type.
     * @return Token type.
     */
    TokenType GetTokenType() const;

    /**
     * @brief Sets token type.
     * @param type Type to set.
     */
    void SetTokenType(TokenType type);

    /**
     * @brief Sets token data type and value is taken from yytext.
     *
     * @param dtype Data type to set.
     */
    void SetData(DataType dtype);

    /**
     * @brief Sets token data type and value.
     *
     * @param dtype Data type to set.
     * @param value Value to set.
     */
    void SetData(DataType dtype, Value value);

    /**
     * @brief Returns token data type as string.
     * @return Data type as string.
     */
    std::string GetTypeString() const override;

    /**
     * @brief Returns token data as string.
     * @return Data as string.
     */
    std::string GetDataString() const;

    /**
     * @brief Returns line number of the token.
     * @return Line number.
     */
    unsigned int GetLineNo() const;

    /**
     * @brief Clones a token.
     * @return Pointer to the new cloned instance.
     */
    Token* Clone() const override;

    /**
     * @brief Returns data type of the token.
     * @return Data type.
     */
    DataType GetDataType() const;

    /**
     * @brief Returns data of the token.
     * @return Data.
     */
    Value GetData() const;

    /**
     * @brief Creates new token instance and pushes it onto the input tape.
     * @details Sets token type and data type.
     *
     * @param ttype Token type.
     * @param dtype Data type.
     */
    static void AddToken(TokenType ttype, DataType dtype);
};

typedef std::list<Token*> InputTape;
extern InputTape inputTape;