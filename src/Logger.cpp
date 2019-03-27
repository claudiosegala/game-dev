#include "Logger.h"
#include <iostream>
#include <string>

#define RED            "\x1b[31m"
#define GREEN          "\x1b[32m"
#define YELLOW         "\x1b[33m"
#define BLUE           "\x1b[34m"
#define MAGENTA        "\x1b[35m"
#define CYAN           "\x1b[36m"
#define RESET          "\x1b[0m"

namespace penguin {

    Logger* Logger::instance;

    bool Logger::logInfoEnabled;

    bool Logger::logWarningEnabled;

    bool Logger::logErrorEnabled;

    Logger::Logger(std::string filename) {
        if (this->instance != nullptr) {
            throw std::runtime_error("There should be only one instance!");
        }

        this->instance = this;
        this->logInfoEnabled = true;
        this->logWarningEnabled = true;
        this->logErrorEnabled = true;

        // TODO: open file
    }

    Logger::~Logger() {
        // TODO: close file
    }

    Logger* Logger::GetInstance () {
        if (Logger::instance == nullptr) {
            // TODO: create a file named log.txt
            throw new std::runtime_error("[PANIC] Wrong use of Logger!");
        }
        
        return Logger::instance;
    }

    Logger* Logger::GetInstance (std::string filename) {
        if (Logger::instance != nullptr) {
            return Logger::instance;
        }
        
        return Logger::instance = new Logger(filename);
    }

    void Logger::Error(std::string msg, int type) {
        auto logger = Logger::GetInstance();

        if (logger->logInfoEnabled) {
            std::cout << RED << "\n";
            if (type == 0 || type == 2) {
                std::cout << "> [error]: ";    
            }

            std::cout << msg;

            if (type == 0 || type == 1) {
                std::cout << "\n\n";
            }
            std::cout << RESET;
        }
    }

    void Logger::Info(std::string msg, int type) {
        auto logger = Logger::GetInstance();

        if (logger->logInfoEnabled) {
            if (type == 0 || type == 2) {
                std::cout << "> [info]: ";    
            }

            std::cout << msg;

            if (type == 0 || type == 1) {
                std::cout << "\n";
            }
        }
    }

    void Logger::Warning(std::string msg, int type) {
        auto logger = Logger::GetInstance();
        
        if (logger->logWarningEnabled) {
            std::cout << YELLOW;
            if (type == 0 || type == 2) {
                std::cout << "> [warn]: ";    
            }

            std::cout << msg;

            if (type == 0 || type == 1) {
                std::cout << "\n";
            }
            std::cout << RESET;
        }
    }
}
