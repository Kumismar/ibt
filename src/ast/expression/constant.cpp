/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-05 10:05
 * @ Modified time: 2024-04-16 13:57
 */

#include "constant.hpp"
#include "expression.hpp"
#include "internal_error.hpp"
#include "token.hpp"
#include <regex>

Constant::Constant(Token& t)
{
    this->type = Constant_t;
    this->data.type = t.GetDataType();
    if (this->data.type == String) {
        this->data.value.stringVal = new std::string((*t.GetData().stringVal));
        return;
    }
    this->data.value = t.GetData();
}

Constant::~Constant()
{
    if (this->data.type == String) {
        delete this->data.value.stringVal;
    }
}

void Constant::PrintTree(std::ofstream& file, int& id, int parentId)
{
    int currentId = id++;
    file << "node" << parentId << " -> node" << currentId << ";\n";
    file << "node" << currentId << " [label=\"Constant: ";
    if (this->data.type == String) {
        // escape double quotes in the original string
        std::string escapedBackslashes = std::regex_replace(*this->data.value.stringVal, std::regex(R"(\\)"), "\\\\");
        file << std::regex_replace(escapedBackslashes, std::regex(R"(")"), "\\\"");
    }
    else if (this->data.type == Int) {
        file << this->data.value.intVal;
    }
    else if (this->data.type == Float) {
        file << this->data.value.floatVal;
    }
    else if (this->data.type == Bool) {
        file << this->data.value.boolVal;
    }
    file << "\"];\n";
}

void Constant::ProcessToken(Token& token)
{
}

void Constant::LinkNode(ASTNode* node, Nonterminal& nt)
{
}