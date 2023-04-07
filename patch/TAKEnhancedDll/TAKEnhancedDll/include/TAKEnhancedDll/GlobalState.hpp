#pragma once

#include "TAKEnhancedDll/common.hpp"
#include "Utils/Logger.h"
#include "TAKCore/Models/UI/GameInterfaceHandler.h"
#include "TAKEnhancedDll/Configs/LauncherConfig.hpp"
#include "TAKEnhancedDll/Configs/UserConfig.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

extern "C" __declspec(dllexport) DWORD setSelectedListItem_fcnAddr;
extern "C" __declspec(dllexport) bool TAKisInitialized;

extern std::shared_ptr<Logger> logger;
extern std::shared_ptr<LauncherConfig> launcherConfig;
extern std::shared_ptr<GameConfig> currentGameConfig;
extern std::shared_ptr<UserConfig> userConfig;

extern HANDLE hProcess;

extern DWORD baseAddress;
extern GameInterfaceHandler* uiHandler;
