#pragma once
#include <string>
#include <Utils/Logger.h>

struct AppConfig
{
    std::string dll;
    std::string target;
    bool debugMode;
    LoggerConfig logger;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    AppConfig, dll, target, debugMode, logger
)