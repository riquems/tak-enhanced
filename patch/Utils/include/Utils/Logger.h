#pragma once
#include "Windows.hpp"
#include <string>
#include <iostream>
#include <format>
#include <stdarg.h>
#include "Utils/json.hpp"

enum class LogLevel
{
    Invalid,
    Verbose,
    Debug,
    Information,
    Warning,
    Error,
    Fatal
};

struct LogToConfig
{
    bool console;
    std::string file;
};

struct LoggerConfig
{
    LogLevel minimumLevel;
    LogToConfig logTo;
};

NLOHMANN_JSON_SERIALIZE_ENUM(LogLevel, {
    { LogLevel::Invalid, "Invalid" },
    { LogLevel::Verbose, "Verbose" },
    { LogLevel::Debug, "Debug" },
    { LogLevel::Information, "Information" },
    { LogLevel::Warning, "Warning" },
    { LogLevel::Error, "Error" },
    { LogLevel::Fatal, "Fatal" }
});

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    LogToConfig, console, file
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    LoggerConfig, minimumLevel, logTo
)

class Logger
{
    LoggerConfig config;
    std::string mode;
    FILE* outputFile = nullptr;

    void raw(const std::string msg, va_list args) const;
    std::string buildMessage(const std::string prefix, const std::string message, const std::string postfix = std::string()) const;
    void logToFile(const std::string msg, va_list args) const;
    void logToConsole(const std::string msg, va_list args) const;

public:
    Logger(LoggerConfig config, std::string mode);
    void debug(const std::string msg, ...) const;
    void info(const std::string msg, ...) const;
    void error(const std::string msg, ...);
    void fatal(const std::string msg, ...) const;
    void context(const std::string msg, ...) const;
    void section(const std::string msg, ...) const;
    void stop();
    LogLevel minimumLevel() const;
};
