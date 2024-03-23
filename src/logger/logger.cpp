/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-23 15:38
 */

#include "logger.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger()
{
    namespace fs = std::filesystem;
    fs::path filePath = fs::path(__FILE__).parent_path().parent_path().parent_path() / "output.log";

    this->file.open(filePath, std::ios::out | std::ios::trunc);
    if (!this->file.is_open()) {
        throw InternalError("Couldn't open file for logging\n");
    }
}

Logger::~Logger()
{
    this->file.close();
}

void Logger::Cleanup()
{
    if (Logger::instance != nullptr) {
        delete Logger::instance;
    }
}

Logger* Logger::GetInstance()
{
    if (Logger::instance == nullptr) {
        Logger::instance = new Logger();
    }
    return Logger::instance;
}

void Logger::AddLeftSide(Symbol* leftSide)
{
    this->leftSideRule = leftSide->Clone();
}

void Logger::AddRightSide(Rule& rightSide)
{
    for (const Symbol* item: rightSide) {
        this->rightSideRule.push_front(item->Clone());
    }
}

void Logger::PrintRule()
{
    this->file << this->leftSideRule->GetTypeString() << " -> ";
    for (const Symbol* item: this->rightSideRule) {
        this->file << item->GetTypeString() << " ";
    }
    this->file << std::endl;
    this->clearRule();
}

void Logger::PrintTokens()
{
    size_t maxTypeLength = 0;
    for (const auto& token: inputTape) {
        maxTypeLength = std::max(maxTypeLength, token->GetTypeString().size());
    }

    // Print tokens with fixed-width columns
    for (const auto& token: inputTape) {
        std::cout << "type: " << std::setw(maxTypeLength) << token->GetTypeString()
                  << "\tdata: " << token->GetDataString().c_str() << "\n";
    }
    std::cout << std::endl;
}

void Logger::clearRule()
{
    delete this->leftSideRule;
    this->leftSideRule = nullptr;
    for (const Symbol* item: this->rightSideRule) {
        delete item;
    }
    this->rightSideRule.clear();
}