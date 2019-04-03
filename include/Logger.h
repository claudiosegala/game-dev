#pragma once

#include <string>

namespace penguin {

    class Logger {
        public:

        ~Logger();

        static Logger* GetInstance();

        static void Init();

        static void Error(const std::string&, int type = 0);

        static void Info(const std::string&, int type = 0);

        static void Warning(const std::string&, int type = 0);

        private:

        static Logger* instance;

        Logger();
    };

}