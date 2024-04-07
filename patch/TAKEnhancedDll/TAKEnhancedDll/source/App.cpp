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
#include <TAKEnhancedLibrary/Keys/KeyCombination.hpp>
#include <Utils/Console.hpp>

__declspec(dllexport) DWORD setSelectedListItem_fcnAddr;
__declspec(dllexport) bool TAKisInitialized;

std::shared_ptr<Logger> logger;
std::shared_ptr<LauncherConfig> launcherConfig;
std::shared_ptr<GameConfig> currentGameConfig;
std::shared_ptr<UserConfig> userConfig;

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

void _init();

void init() {
    try {
        _init();
    }
    catch (const std::exception& e) {
        if (logger != nullptr) {
            logger->fatal(e.what());
        }
        else {
            auto errorCode = GetLastError();
            std::cout << "[Fatal]" << e.what() << " Error Code: " << std::to_string(errorCode) << "\n";
        }
    }
}

void _init()
{
    StartConsole();
    
    std::cout << "[Info] App start" << "\n";

    auto loggerConfigPath = "./TAKEnhanced/logger.cfg.json";
    std::cout << "[Info] Loading logger config from " << loggerConfigPath << "\n";
    auto maybeLoggerConfig = fromJson<LoggerConfig>(loggerConfigPath);

    if (!maybeLoggerConfig.has_value()) {
        std::cout << "[Info] Logger config not found, using the default one." << '\n';
        maybeLoggerConfig = LoggerConfig {};
    }

    auto loggerConfig = maybeLoggerConfig.value();

    logger = std::make_shared<Logger>(loggerConfig, "a");

    auto launcherConfigPath = "./TAKEnhanced/launcher.cfg.json";
    logger->info("Loading launcher config from %s", launcherConfigPath);
    auto maybeLauncherConfig = fromJson<LauncherConfig>(launcherConfigPath);

    if (!maybeLauncherConfig.has_value()) {
        logger->info("Launcher config not found, using the default one.");
        maybeLauncherConfig = LauncherConfig {};
    }

    launcherConfig = std::make_shared<LauncherConfig>(maybeLauncherConfig.value());

    logger->info("Loading presets from %s", maybeLauncherConfig.value().presetsPath.c_str());
    auto presets = Presets(getPresets(maybeLauncherConfig.value().presetsPath));

    if (presets.empty()) {
        logger->info("No presets were found at specified path.");
    }
    else {
        logger->info("Found: ");

        for (auto& preset : presets.asVector()) {
            logger->info("- " + preset.name);
        }

        auto currentGameConfigPath = "./TAKEnhanced/game.cfg.json";
        logger->info("Loading current game config from %s", currentGameConfigPath);
        auto maybeCurrentGameConfig = fromJson<GameConfig>(currentGameConfigPath);

        if (!maybeCurrentGameConfig.has_value()) {
            logger->info("Current game config not found, using the default one.");
            maybeCurrentGameConfig = GameConfig {};
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

    auto userConfigPath = "./TAKEnhanced/user.cfg.json";
    logger->info("Loading user config from %s", userConfigPath);
    auto maybeUserConfig = fromJson<UserConfig>(userConfigPath);

    if (!maybeUserConfig.has_value()) {
        logger->info("User config not found, using the default one.");
        maybeUserConfig = UserConfig {};
    }

    userConfig = std::make_shared<UserConfig>(maybeUserConfig.value());

    UserConfig defaultUserConfig;

    for (const auto& defaultKeyBinding : defaultUserConfig.keyBindings) {
        bool containsCommand = dky::contains(userConfig->keyBindings, [&](const KeyBinding& keyBinding) {
            return commandStringParser.toString(*keyBinding.command) == commandStringParser.toString(*defaultKeyBinding.command);
        });

        if (!containsCommand) {
            userConfig->keyBindings.push_back(defaultKeyBinding);
        }
    }

    exePath = std::filesystem::current_path();
    baseAddress = getProcessBaseAddress("Kingdoms.icd");
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
        toJson(loggerConfig, "./TAKEnhanced/logger.cfg.json");
    };

    launcher.show();

    logger->section("CHANGES");
    applyChanges(currentGameConfig, logger);

    std::thread TAKEnhancedServiceThread(startTAKEnhancedService, std::ref(currentGameConfig));
    TAKEnhancedServiceThread.detach();
}
