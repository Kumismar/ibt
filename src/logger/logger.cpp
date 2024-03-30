/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-03-30 21:02
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

void Logger::AddTokenToRecents(Token& token)
{
    this->recentTokens.push_front(token.Clone());
    if (this->recentTokens.size() > 10) {
        delete this->recentTokens.back();
        this->recentTokens.pop_back();
    }
}

void Logger::PrintSyntaxError(const char* message)
{
    std::string red = "\033[1;31m";
    std::string reset = "\033[0m";
    std::cerr << red << "Syntax error: "
              << reset << message;

    // Get position of the error
    size_t position = 0;
    for (const auto& token: this->recentTokens) {
        position += token->GetDataString().size() + 1; // for space between tokens
    }

    // Print recent tokens
    for (auto it = this->recentTokens.rbegin(); it != this->recentTokens.rend(); it++) {
        std::cerr << (*it)->GetDataString() << " ";
    }

    // Print max three more tokens
    int i = 0;
    for (const auto& token: inputTape) {
        if (i >= 3) {
            break;
        }
        std::cerr << token->GetDataString() << " ";
        i++;
    }

    // Print error position
    std::cerr << "\n";
    for (size_t i = 0; i < position; i++) {
        std::cerr << " ";
    }
    std::cerr << red << "^" << reset << std::endl;
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