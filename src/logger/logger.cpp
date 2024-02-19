#include "logger.hpp"
#include "internal_error.hpp"
#include "stack_item.hpp"
#include <filesystem>
#include <fstream>

Logger* Logger::instance = nullptr;

Logger::Logger()
{
    namespace fs = std::filesystem;
    fs::path filePath = "../../output.log";

    // Clear current file contents
    this->file.open(filePath, std::ios::trunc);
    this->file.close();

    this->file.open(filePath, std::ios::app);
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
    this->leftSideRule = dynamic_cast<Nonterminal*>(leftSide);
    if (this->leftSideRule == nullptr) {
        throw InternalErrorException("Left side of the rule has to be a Nonterminal\n");
    }
}

void Logger::AddRightSide(std::list<StackItem*>& rightSide)
{
    this->rightSideRule = rightSide;
}

void Logger::PrintRule()
{
    this->file << this->leftSideRule->GetTypeString() << " -> ";
    for (auto it = this->rightSideRule.crbegin(); it != this->rightSideRule.crend(); it++) {
        this->file << (*it)->GetTypeString() << " ";
    }
    this->file << std::endl;
    this->leftSideRule = nullptr;
    this->rightSideRule.clear();
}