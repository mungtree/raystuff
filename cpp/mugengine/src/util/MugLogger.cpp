//
// Created by meet on 5/31/25.
//

#include "MugLogger.hpp"

#ifdef USE_SPDLOG
bool MugLogger::hasInit = []() -> bool {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    spdlog::info("Initializing Logger");
    return true;
};

void MugLogger::init() {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Initializing Logger");
}
MugLogger::MugLogger() {
}

void MugLogger::debug(const std::string &message) {
    spdlog::debug(message);
}

void MugLogger::info(const std::string& message) {
    spdlog::info(message);
}

void MugLogger::warn(const std::string& message) {
    spdlog::warn(message);
}

void MugLogger::error(const std::string& message) {
    spdlog::error(message);
}

void MugLogger::critical(const std::string& message) {
    spdlog::critical(message);
}

#else
bool MugLogger::hasInit = false;
MugLogger::MugLogger() {
    info("Using std::cout logger");
}

void MugLogger::init() {
    hasInit = true;
}

void MugLogger::debug(const std::string &message) {
    std::cout << "[Debug]\t" << message << std::endl;
}

void MugLogger::info(const std::string &message) {
    std::cout << "[Info]\t" << message << std::endl;
}

void MugLogger::warn(const std::string &message) {
    std::cerr << "[WARN]\t" << message << std::endl;
}

void MugLogger::error(const std::string &message) {
    std::cerr << "[ERROR]\t" << message << std::endl;
}

void MugLogger::critical(const std::string &message) {
    std::cerr << "[CRITICAL]\t" << message << std::endl;
}


#endif
