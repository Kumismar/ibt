/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-04-28 21:19
 * @ Modified time: 2024-04-28 21:50
 */

#pragma once

#include "predictive_parser.hpp"

class ExpressionProcessor
{
private:
    AnalysisStack& stack;

    void pushPrecedence();

public:
    ExpressionProcessor(AnalysisStack& stack);
    void Reduce();
    void Shift();
    void Push();
};