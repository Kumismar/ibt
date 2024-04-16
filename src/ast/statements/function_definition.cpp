/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-16 14:41
 */

#include "function_definition.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"
#include "token.hpp"

void Parameter::SetType(const TokenType type)
{
    this->type = type;
}

void Parameter::SetName(const std::string& name)
{
    this->name = name;
}

void Parameter::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"Parameter\"];\n";

    file << "node" << currentId << " -> node" << ++currentId << ";\n";
    id++;
    file << "node" << currentId << " [label=\"Name: " << this->name << "\"];\n";

    file << "node" << currentId << " -> node" << ++currentId << ";\n";
    id++;
    file << "node" << currentId << " [label=\"Type: " << this->type << "\"];\n";
}

FunctionDefinition::FunctionDefinition()
{
    this->type = FuncDef_s;
}

FunctionDefinition::~FunctionDefinition()
{
    if (currentParam != nullptr) {
        delete currentParam;
        this->params.pop_back();
    }

    if (!this->params.empty()) {
        for (auto param: this->params) {
            delete param;
        }
        this->params.clear();
    }


    if (this->body != nullptr) {
        delete this->body;
    }
}

void FunctionDefinition::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"FunctionDefinition\"];\n";

    int functionId = currentId;
    file << "node" << currentId << "-> node" << ++currentId << ";\n";
    id++;
    file << "node" << currentId << " [label=\"Name: " << this->name << "\"];\n";

    for (auto param: this->params) {
        param->PrintTree(file, id, functionId);
    }

    currentId = id++;
    file << "node" << functionId << "-> node" << ++currentId << ";\n";
    id++;
    file << "node" << currentId << " [label=\"ReturnType: " << this->returnType << "\"];\n";
    this->body->PrintTree(file, id, functionId);
}

void FunctionDefinition::ProcessToken(Token& token)
{
    if (this->isType(token)) {
        if (**std::next(inputTape.begin()) == tLCurl) { // next token is '{'
            this->setReturnType(token);
        }
        else {
            this->currentParam = new Parameter();
            this->currentParam->SetType(token.GetTokenType());
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
    if (nt.GetNonterminalType() == nStatements) {
        StatementList* tmp = dynamic_cast<StatementList*>(node);
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