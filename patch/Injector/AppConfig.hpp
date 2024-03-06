#pragma once
#include <string>
#include <Utils/Logger.h>

struct AppConfig
{
    std::string dll = "TAKEnhanced/TAKEnhanced.dll";
    std::string target = "Kingdoms.icd";
    bool debugMode = false;
    LoggerConfig logger;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    AppConfig, dll, target, debugMode, logger
)
