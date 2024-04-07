/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-07 22:56
 */

#include "function_definition.hpp"
#include "code_block.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"
#include "token.hpp"

void Parameter::SetType(const DataType type)
{
    this->type = type;
}

void Parameter::SetName(const std::string& name)
{
    this->name = name;
}

FunctionDefinition::FunctionDefinition()
{
    this->type = FuncDef_s;
}

void FunctionDefinition::ProcessToken(Token& token)
{
    if (this->isType(token)) {
        if (this->body == nullptr) {
            this->currentParam = new Parameter();
            this->currentParam->SetType(token.GetDataType());
        }
        else {
            this->setReturnType(token);
        }
    }
    else if (token == tVariable) {
        if (this->currentParam == nullptr) {
            throw InternalError("FunctionDefinition::ProcessToken currentParam is nullptr");
        }

        this->currentParam->SetName(token.GetDataString());
        this->params.push_back(this->currentParam);
    }
    else if (token == tFuncName) {
        this->name = token.GetDataString();
    }
}

void FunctionDefinition::LinkNode(ASTNode* node, Nonterminal& nt)
{
    if (nt.GetNonterminalType() == nCodeBlock) {
        CodeBlock* tmp = dynamic_cast<CodeBlock*>(node);
        if (tmp == nullptr) {
            throw InternalError("FunctionDefiniton::LinkNode (case nCodeBlock) invalid type: " + std::string(typeid(*node).name()));
        }

        this->body = tmp;
    }
}

bool FunctionDefinition::isType(const Token& token) const
{
    return (token == tInt || token == tFloat || token == tString || token == tBool);
}

void FunctionDefinition::setReturnType(const Token& token)
{
    switch (token.GetTokenType()) {
        case tInt: {
            this->returnType = Int;
            break;
        }
        case tFloat: {
            this->returnType = Float;
            break;
        }
        case tBool: {
            this->returnType = Bool;
            break;
        }
        case tString: {
            this->returnType = String;
            break;
        }
        default: {
            throw InternalError("FunctionDefinition::setReturnType invalid token type: " + token.GetTypeString());
        }
    }
}