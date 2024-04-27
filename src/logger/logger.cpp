/**
 * @ Author: Ondřej Koumar
 * @ Email: xkouma02@stud.fit.vutbr.cz
 * @ Create Time: 2024-03-18 19:12
 * @ Modified time: 2024-04-15 19:13
 */

#include "logger.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"
#include "token.hpp"
#include <filesystem>
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
    if (Logger::instance == nullptr) {
        return;
    }

    if (!Logger::instance->recentTokens.empty()) {
        for (const Token* token: Logger::instance->recentTokens) {
            delete token;
        }
        Logger::instance->recentTokens.clear();
    }
    delete Logger::instance;
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
    for (auto & symbol : rightSide) {
        this->rightSideRule.push_front(symbol->Clone());
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

void Logger::PrintTokens() const
{
    if (!this->enableDebugPrint) {
        return;
    }

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
    if (token == tFuncConst) {
        return;
    }

    this->recentTokens.push_front(token.Clone());
    if (this->recentTokens.size() > 10) {
        delete this->recentTokens.back();
        this->recentTokens.pop_back();
    }
}

void Logger::PrintSyntaxError(const char* message)
{
    if (this->recentTokens.empty()) {
        std::cerr << this->red << "File is empty!" << this->reset << std::endl;
        return;
    }

    std::cerr << this->red << "Syntax error "
              << this->reset << "near line " << std::to_string(this->recentTokens.front()->GetLineNo()) << ": " << message;

    // Get position of the error
    size_t position = 0;
    for (const auto& token: this->recentTokens) {
        position += token->GetDataString().size() + 1; // for space between tokens
    }

    // Print recent tokens
    for (auto it = this->recentTokens.rbegin(); it != this->recentTokens.rend(); it++) {
        std::cerr << (*it)->GetDataString() << " ";
    }

    // Print max three more tokens from input tape
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
    for (size_t j = 0; j < position; j++) {
        std::cerr << " ";
    }
    std::cerr << this->red << "^" << this->reset << std::endl;
}

void Logger::PrintLexicalError(const char* message)
{
    std::cerr << this->red << "Lexical error " << this->reset << message;
}

void Logger::PrintUsageError(const char* message)
{
    std::string boldRed = "\033[1;31m";
    std::string underlined = "\033[4m";

    std::cerr << boldRed << "Usage error: " << this->reset << message
              << "Usage: build/src/Parser " << underlined << "[-d]" << this->reset << " "
              << underlined << "-f" << this->reset << " " << underlined << "<filename>\n"
              << this->reset;
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

void Logger::EnableDebugPrint()
{
    this->enableDebugPrint = true;
}