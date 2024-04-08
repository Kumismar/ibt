/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-08 11:02
 * @ Modified time: 2024-04-08 12:52
 */

#include "variable.hpp"
#include "operand.hpp"
#include "token.hpp"

Variable::Variable(Token& token)
{
    this->type = Variable_t;
    this->data.type = token.GetDataType();
    Value tokenData = token.GetData();
    if (this->data.type == String) {
        this->data.value.stringVal = new std::string(*tokenData.stringVal);
    }
    else {
        this->data.value = tokenData;
    }
}

Variable::~Variable()
{
    if (this->data.type == String) {
        delete this->data.value.stringVal;
    }
}