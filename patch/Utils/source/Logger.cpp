#include "Utils/Logger.h"

Logger::Logger(LoggerConfig config, std::string mode) {
    this->config = config;
    this->mode = mode;

    if (!this->config.logTo.file.empty())
        this->outputFile = _fsopen(this->config.logTo.file.c_str(), this->mode.c_str(), _SH_DENYNO);
}

void Logger::debug(const std::string msg, ...) const {
    if (this->config.minimumLevel > LogLevel::Debug) {
        return;
    }

    va_list args;
    va_start(args, msg);

    this->raw(this->buildMessage("[Debug]", msg), args);
}

void Logger::info(const std::string msg, ...) const {
    if (this->config.minimumLevel > LogLevel::Information) {
        return;
    }

    va_list args;
    va_start(args, msg);

    this->raw(this->buildMessage("[Info]", msg), args);
}

void Logger::error(const std::string msg, ...) {
    if (this->config.minimumLevel > LogLevel::Error) {
        return;
    }

    va_list args;
    va_start(args, msg);

    this->raw(this->buildMessage("[Error]", msg), args);
    std::cin.get();
}

void Logger::fatal(const std::string msg, ...) const {
    if (this->config.minimumLevel > LogLevel::Error) {
        return;
    }

    va_list args;
    va_start(args, msg);

    auto errorCode = GetLastError();
    this->raw(this->buildMessage("[Fatal]", msg, " Error Code: " + std::to_string(errorCode)), args);
    std::cin.get();
}

std::string Logger::buildMessage(const std::string prefix, const std::string message, const std::string postfix) const {
    return prefix + " " + message + postfix + "\n";
}

void Logger::raw(const std::string msg, va_list args) const {
    if (this->config.logTo.console) {
        this->logToConsole(msg, args);
    }

    if (!this->config.logTo.file.empty()) {
        this->logToFile(msg, args);
    }

    va_end(args);
}

void Logger::logToConsole(const std::string msg, va_list args) const
{
    vprintf(msg.c_str(), args);
}

void Logger::logToFile(const std::string msg, va_list args) const
{
    vfprintf(outputFile, msg.c_str(), args);
    fflush(outputFile);
}

void Logger::section(const std::string section, ...) const {
    va_list args;
    va_start(args, section);

    this->raw("\n[" + section + "]\n\n", args);
}

void Logger::context(const std::string context, ...) const {
    if (this->config.minimumLevel > LogLevel::Error) {
        return;
    }

    va_list args;
    va_start(args, context);

    this->raw("\n### " + context + " ###\n\n", args);
}

void Logger::stop() {
    fclose(this->outputFile);
}
