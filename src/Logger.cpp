#include <Logger.h>
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

    Logger::Logger(const std::string &filename) {
        if (this->instance != nullptr) {
            throw std::runtime_error("There should be only one instance!");
        }

        this->instance = this;

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

    Logger* Logger::GetInstance (const std::string &filename) {
        if (Logger::instance != nullptr) {
            return Logger::instance;
        }
        
        return Logger::instance = new Logger(filename);
    }

    void Logger::Init (const std::string &filename) {
        (void)GetInstance(filename);
    }

    void Logger::Error(const std::string &msg, int type) {
        #ifdef LOG_ERROR
            std::cout << RED << "\n";
            if (type == 0 || type == 2) {
                std::cout << "> [error]: ";    
            }

            std::cout << msg;

            if (type == 0 || type == 1) {
                std::cout << "\n\n";
            }
            std::cout << RESET;
        #else
            // Avoid warnings
            (void)msg;
            (void)type;
        #endif
    }

    void Logger::Info(const std::string &msg, int type) {
        #ifdef LOG_INFO
            if (type == 0 || type == 2) {
                std::cout << "> [info]: ";    
            }

            std::cout << msg;

            if (type == 0 || type == 1) {
                std::cout << "\n";
            }
        #else
            // Avoid warnings
            (void)msg;
            (void)type;
        #endif
    }

    void Logger::Warning(const std::string &msg, int type) {
        #ifdef LOG_WARN
            std::cout << YELLOW;
            if (type == 0 || type == 2) {
                std::cout << "> [warn]: ";    
            }

            std::cout << msg;

            if (type == 0 || type == 1) {
                std::cout << "\n";
            }
            std::cout << RESET;
        #else
            // Avoid warnings
            (void)msg;
            (void)type;
        #endif
    }
}
