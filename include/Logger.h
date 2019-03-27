#pragma once

#include <string>

namespace penguin {

    class Logger {
        public:

        static bool logInfoEnabled;

        static bool logWarningEnabled;

        static bool logErrorEnabled;

        ~Logger();

        static Logger* GetInstance();

        static Logger* GetInstance(std::string);

        static void Error(std::string, int type = 0);

        static void Info(std::string, int type = 0);

        static void Warning(std::string, int type = 0);

        private:

        static Logger* instance;

        Logger(std::string);
    };

}