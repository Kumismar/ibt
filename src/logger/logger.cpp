#include "logger.hpp"
#include "internal_error.hpp"
#include "nonterminal.hpp"
#include "precedence_symbol.hpp"
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
        throw InternalErrorException("Couldn't open file for logging\n");
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

void Logger::AddLeftSide(StackItem* leftSide)
{
    this->leftSideRule = leftSide->Clone();
}

void Logger::AddRightSide(std::list<StackItem*>& rightSide)
{
    for (const StackItem* item: rightSide) {
        this->rightSideRule.push_back(item->Clone());
    }
}

void Logger::PrintRule()
{
    this->file << this->leftSideRule->GetTypeString() << " -> ";
    for (auto it = this->rightSideRule.crbegin(); it != this->rightSideRule.crend(); it++) {
        this->file << (*it)->GetTypeString() << " ";
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
    for (const StackItem* item: this->rightSideRule) {
        delete item;
    }
    this->rightSideRule.clear();
}