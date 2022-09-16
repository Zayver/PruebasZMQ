#include <iostream>
#include <syncstream>
#include <chrono>
class Logger{
    std::osyncstream synced_out;
  public:
    Logger();
    enum class type{
        INFO,
        WARN,
        DEBUG,
        ERROR
    };
    void log(const type, const std::string &) const noexcept;
};