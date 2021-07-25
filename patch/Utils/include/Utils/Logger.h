#pragma once
#include "HelperFunctions.hpp"

enum LogLevel
{
    VERBOSE_LEVEL,
    DEBUG_LEVEL,
    INFORMATION_LEVEL,
    WARNING_LEVEL,
    ERROR_LEVEL
};

class Logger
{
public:
    FILE* outputFile = nullptr;

    LogLevel MinimumLevel = LogLevel::INFORMATION_LEVEL;

    Logger() {}

    Logger(std::string fileName, std::string mode, LogLevel minimumLevel)
    {
        outputFile = _fsopen(fileName.c_str(), mode.c_str(), _SH_DENYNO);

        MinimumLevel = minimumLevel;
    }

    void initialize(std::string fileName, std::string mode, LogLevel minimumLevel)
    {
        outputFile = _fsopen(fileName.c_str(), mode.c_str(), _SH_DENYNO);

        MinimumLevel = minimumLevel;
    }

    void log(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        logToConsole(NULL, fmt, args);
        logToFile(NULL, fmt, args);
    }

    void logToConsole(const char* prefix, const char* fmt, va_list args)
    {
        if (prefix != NULL) {
            printf(prefix);
        }

        vprintf(fmt, args);
        printf("%c", '\n');
    }

    void logToFile(const char* prefix, const char* fmt, va_list args)
    {
        if (prefix != NULL) {
            fprintf(outputFile, prefix);
        }

        vfprintf(outputFile, fmt, args);
        fprintf(outputFile, "\n");

        fflush(outputFile);
    }

    void debug(const char* fmt, ...)
    {
        if (MinimumLevel > DEBUG_LEVEL) {
            return;
        }

        va_list args;
        va_start(args, fmt);

        logToConsole("[DBG] ", fmt, args);
        logToFile("[DBG] ", fmt, args);
    }

    void information(const char* fmt, ...)
    {
        if (MinimumLevel > INFORMATION_LEVEL) {
            return;
        }

        va_list args;
        va_start(args, fmt);

        logToConsole("[INF] ", fmt, args);
        logToFile("[INF] ", fmt, args);
    }

    void warning(const char* fmt, ...)
    {
        if (MinimumLevel > WARNING_LEVEL) {
            return;
        }

        va_list args;
        va_start(args, fmt);

        logToConsole("[WRN] ", fmt, args);
        logToFile("[WRN] ", fmt, args);
    }

    void error(const char* fmt, ...)
    {
        if (MinimumLevel > ERROR_LEVEL) {
            return;
        }

        va_list args;
        va_start(args, fmt);

        logToConsole("[ERR] ", fmt, args);
        printf(" Error Code: %lu", GetLastError());
        printf("\n\nFor further information, contact DeeKay with this error code:\nE-Mail: Henrique-MS@Outlook.com\nGameRanger ID: 1184157\nDiscord: DeeKay#3610\n");
        printf("%c", '\n');

        printf("[ERR] ");
        vfprintf(outputFile, fmt, args);
        fprintf(outputFile, " Error Code: %lu", GetLastError());
        fprintf(outputFile, "\n\nFor further information, contact DeeKay with this error code:\nE-Mail: Henrique-MS@Outlook.com\nGameRanger ID: 1184157\nDiscord: DeeKay#3610\n");
        fprintf(outputFile, "%c", '\n');

        fflush(outputFile);
    }

    void section(const char* str)
    {
        fprintf(outputFile, "[%s]\n\n", str);

        fflush(outputFile);
    }

    void context(const char* str)
    {
        fprintf(outputFile, "### %s ###\n\n", str);

        fflush(outputFile);
    }

    void end()
    {
        fclose(outputFile);
    }
};