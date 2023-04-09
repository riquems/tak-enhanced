#include "TAKEnhancedDll/App.hpp"

#pragma pack(push, 8)
#include <Windows.h>
#pragma pack(pop)

#include <cstdlib>
#include <ctime>
#include <thread>

#include <iostream>
#include <map>
#include <memory>
#include <chrono>
#include <algorithm>
#include <fstream>
#include "TAKEnhancedDll/Configs/LauncherConfig.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"
#include "TAKCore/Models/UI/GameInterfaceHandler.h"
#include "Utils/Logger.h"
#include "TAKCore/Functions/FunctionsOffsets.h"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Models/Side.h"
#include "TAKCore/Models/UI/Window.h"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedLauncher/main_form.hpp"
#include "TAKEnhancedDll/Changes.hpp"
#include "TAKEnhancedDll/TAKEnhancedService.hpp"
#include <TAKEnhancedDll/Keys/KeyCombination.hpp>
#include <Utils/Console.hpp>

__declspec(dllexport) DWORD setSelectedListItem_fcnAddr;
__declspec(dllexport) bool TAKisInitialized;

std::shared_ptr<Logger> logger;
std::shared_ptr<LauncherConfig> launcherConfig;
std::shared_ptr<GameConfig> currentGameConfig;
std::shared_ptr<UserConfig> userConfig;

Commands commands;
CommandStringParser commandStringParser(commands);

Keys keys;
KeyCombinationStringParser keyCombinationStringParser(keys);

std::filesystem::path exePath;
HANDLE hProcess = nullptr;

DWORD baseAddress = 0;
GameInterfaceHandler* uiHandler = nullptr;

template<typename T>
std::optional<T> fromJson(std::string path)
{
    std::ifstream fileStream(path);

    if (!fileStream.is_open()) {
        return std::optional<T>();
    }

    json json;
    fileStream >> json;

    auto config = json.get<T>();

    return config;
}

void toJson(json j, std::string path)
{
    std::ofstream fileStream(path);

    fileStream << std::setw(2) << j;
}

std::vector<Preset> getPresets(std::string configsPath)
{
    std::vector<Preset> configs;
    
    std::vector<std::filesystem::path> files = files::get(configsPath, ".preset.json", true);

    for (auto file : files) {
        std::fstream fileStream(file);

        json json;
        fileStream >> json;

        Preset config = json.get<Preset>();

        configs.push_back(config);
    }

    return configs;
}

void init()
{
    StartConsole();
    
    std::cout << "[Info] App start" << "\n";
    std::cout << "[Info] Loading logger config..." << "\n";
    auto maybeLoggerConfig = fromJson<LoggerConfig>("./TAKEnhanced/logger.cfg.json");

    if (!maybeLoggerConfig.has_value()) {
        std::cout << "[Error] Logger config not found." << '\n';
        return;
    }

    auto loggerConfig = maybeLoggerConfig.value();

    logger = std::make_shared<Logger>(loggerConfig, "a");

    logger->info("Loading launcher config...");
    auto maybeLauncherConfig = fromJson<LauncherConfig>("./TAKEnhanced/launcher.cfg.json");

    if (!maybeLauncherConfig.has_value()) {
        logger->error("Launcher config not found.");
        return;
    }

    launcherConfig = std::make_shared<LauncherConfig>(maybeLauncherConfig.value());

    logger->info("Loading presets at %s", maybeLauncherConfig.value().presetsPath.c_str());
    auto presets = Presets(getPresets(maybeLauncherConfig.value().presetsPath));

    if (presets.empty()) {
        logger->info("No presets were found at specified path.");
    }
    else {
        logger->info("Found: ");

        for (auto& preset : presets.asVector()) {
            logger->info("- " + preset.name);
        }

        logger->info("Loading current game config...");

        std::optional<GameConfig> maybeCurrentGameConfig = fromJson<GameConfig>("./TAKEnhanced/game.cfg.json");;

        if (!maybeLauncherConfig.has_value()) {
            logger->error("Current game config not found. (searching for %s)", "./TAKEnhanced/game.cfg.json");
            return;
        }

        auto currentGameConfigValue = maybeCurrentGameConfig.value();

        if (launcherConfig->currentPreset != "Custom") {
            auto preset = presets.find(
                [&](Preset preset)->bool {
                    return preset.name == launcherConfig->currentPreset;
                }
            );

            if (!preset.has_value()) {
                logger->error("Preset not found. (searching for %s)", launcherConfig->currentPreset.c_str());
                return;
            }

            // apply preset over the config
            // currentGameConfigValue = preset.value();
        }

        currentGameConfig = std::make_shared<GameConfig>(currentGameConfigValue);
    }

    logger->info("Loading user config...");
    auto maybeUserConfig = fromJson<UserConfig>("./TAKEnhanced/user.cfg.json");

    if (!maybeUserConfig.has_value()) {
        logger->error("User config not found.");
        return;
    }

    userConfig = std::make_shared<UserConfig>(maybeUserConfig.value());

    exePath = std::filesystem::current_path();
    baseAddress = getProcessBaseAddress("Kingdoms.icd");
    TAK::init(baseAddress);
    logger->debug("Process base address loaded successfully.");

    hProcess = GetCurrentProcess();
    logger->debug("Current process loaded successfully.");

    // Initialize Global Pointers
    uiHandler = (GameInterfaceHandler*)(GlobalPointers::GameInterfaceHandler + baseAddress);
    gameWrapper = std::make_shared<GameWrapper>(uiHandler, baseAddress);

    // Initialize functions
    setSelectedListItem_fcnAddr = *(DWORD*) (FunctionsOffsets::changeSelectedItem + baseAddress);

    nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));
    nana::rectangle fm_rect = nana::API::make_center(launcherConfig->window.width, launcherConfig->window.height);

    main_form launcher(
        fm_rect,
        launcherConfig,
        currentGameConfig,
        userConfig,
        std::make_shared<Presets>(presets),
        std::make_shared<PresetApplier>(),
        std::make_shared<Commands>(commands),
        std::make_shared<Keys>(keys),
        std::make_shared<CommandStringParser>(commandStringParser),
        std::make_shared<KeyCombinationStringParser>(keyCombinationStringParser),
        logger
    );

    launcher.on_save = [&]() {
        logger->info("Saving changes...");
        toJson(*launcherConfig, "./TAKEnhanced/launcher.cfg.json");
        toJson(*currentGameConfig, "./TAKEnhanced/game.cfg.json");
        toJson(*userConfig, "./TAKEnhanced/user.cfg.json");
    };

    launcher.show();

    logger->section("CHANGES");
    applyChanges(currentGameConfig, logger);

    std::thread TAKEnhancedServiceThread(startTAKEnhancedService, std::ref(currentGameConfig));
    TAKEnhancedServiceThread.detach();
}
