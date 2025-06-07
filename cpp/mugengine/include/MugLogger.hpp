//
// Created by meet on 5/31/25.
//

#ifndef MUGLOGGER_H
#define MUGLOGGER_H
#include <string>
#ifdef USE_SPDLOG
#include <spdlog/spdlog.h>
#else
#include <iostream>
#endif

class MugLogger {
private:
    static bool hasInit;
public:
    MugLogger();

    static void init();

    static void debug(const std::string& message);

    static void info(const std::string &message);

    static void warn(const std::string& message);

    static void error(const std::string& message);

    static void critical(const std::string& message);
};



#endif //MUGLOGGER_H
