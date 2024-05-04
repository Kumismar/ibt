/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-05-03 11:13
 */

#include "function_definition.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "statement.hpp"
#include "token.hpp"

void Parameter::SetType(const TokenType t)
{
    this->type = t;
}

void Parameter::SetName(const std::string& n)
{
    this->name = n;
}

void Parameter::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"Parameter\"];\n";

    int paramId = currentId;
    int nameId = ++currentId;
    file << "node" << paramId << " -> node" << nameId << ";\n";
    id++;
    file << "node" << nameId << " [label=\"Name: " << this->name << "\"];\n";

    int typeId = ++currentId;
    file << "node" << paramId << " -> node" << typeId << ";\n";
    id++;
    file << "node" << typeId << " [label=\"Type: " << Parameter::typeToString(this->type) << "\"];\n";
}

FunctionDefinition::FunctionDefinition()
{
    this->nodeType = FuncDef_n;
    this->type = FuncDef_s;
    this->returnType = DataType::None;
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
    delete this->body;
}

void FunctionDefinition::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"FunctionDefinition\"];\n";

    int functionId = currentId;
    int functionNameId = ++currentId;
    file << "node" << functionId << "-> node" << functionNameId << ";\n";
    id++;
    file << "node" << functionNameId << " [label=\"Name: " << this->name << "\"];\n";

    for (auto param: this->params) {
        param->PrintTree(file, id, functionId);
    }

    currentId = id++;
    int returnTypeId = ++currentId;
    file << "node" << functionId << "-> node" << returnTypeId << ";\n";
    id++;
    file << "node" << returnTypeId << " [label=\"ReturnType: " << FunctionDefinition::typeToString(this->returnType) << "\"];\n";
    this->body->PrintTree(file, id, functionId);
}

void FunctionDefinition::ProcessToken(Token& token)
{
    if (FunctionDefinition::isType(token)) {
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
        auto* tmp = dynamic_cast<StatementList*>(node);
        if (tmp == nullptr) {
            throw InternalError("FunctionDefiniton::LinkNode (case nCodeBlock) invalid type: " + std::string(typeid(*node).name()));
        }

        this->body = tmp;
    }
}

bool FunctionDefinition::isType(const Token& token)
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

std::string Parameter::typeToString(TokenType t)
{
    switch (t) {
        case tInt: {
            return "Int";
        }
        case tFloat: {
            return "Float";
        }
        case tBool: {
            return "Bool";
        }
        case tString: {
            return "String";
        }
        default: {
            throw InternalError("FunctionDefinition::typeToString invalid token type: " + std::to_string(t));
        }
    }
}

std::string FunctionDefinition::typeToString(DataType t)
{
    switch (t) {
        case Int: {
            return "Int";
        }
        case Float: {
            return "Float";
        }
        case Bool: {
            return "Bool";
        }
        case String: {
            return "String";
        }
        default: {
            throw InternalError("FunctionDefinition::typeToString invalid data type: " + std::to_string(t));
        }
    }
}