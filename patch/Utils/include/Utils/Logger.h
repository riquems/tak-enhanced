#pragma once
#include "HelperFunctions.hpp"

class Logger
{
public:
    FILE* outputFile = nullptr;

    Logger() {}

    Logger(std::string fileName, std::string mode)
    {
        outputFile = _fsopen(fileName.c_str(), mode.c_str(), _SH_DENYNO);
    }

    void initialize(std::string fileName, std::string mode)
    {
        outputFile = _fsopen(fileName.c_str(), mode.c_str(), _SH_DENYNO);
    }

    void log(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        vfprintf(outputFile, fmt, args);
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

    void error(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);

        vfprintf(outputFile, fmt, args);
        fprintf(outputFile, " Error Code: %lu", GetLastError());
        fprintf(outputFile, "\n\nFor further information, contact DeeKay with this error code:\nE-Mail: Henrique-MS@Outlook.com\nGameRanger ID: 1184157\nDiscord: DeeKay#3610\n");
        fprintf(outputFile, "%c", '\n');

        fflush(outputFile);
    }

    void end()
    {
        fclose(outputFile);
    }
};