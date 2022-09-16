#include <chrono>
#include <iostream>
#include <string>
#include "logger.hpp"

Logger::Logger(): synced_out{std::cout}{}
void Logger::log(const Logger::type type, const std::string & msm) const noexcept{
    std::string level;
    switch (type) {
        case type::INFO:
            level = "INFO";
            break;
        case type::WARN:
            level = "WARN";
            break;
        case type::ERROR:
            level = "ERROR";
            break;
        case type::DEBUG:
            level = "DEBUG";
            break;
    }
}