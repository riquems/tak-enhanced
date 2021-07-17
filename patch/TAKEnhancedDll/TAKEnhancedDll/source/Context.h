#pragma once
#pragma pack(push, 8)
#include <Windows.h>
#pragma pack(pop)

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <map>
#include <memory>
#include <chrono>
#include <algorithm>
#include "Models/UI/GameInterfaceHandler.h"

DWORD baseAddress = 0;
GameInterfaceHandler* uiHandler = nullptr;

#include "Utils/Logger.h"
#include "Functions/FunctionsOffsets.h"
#include "GlobalPointers/GlobalPointers.h"
#include "GameFunctions.h"
#include "Models/Side.h"
#include "./Wrappers/GameWrapper.h"
#include "./Wrappers/MatchWrapper.h"
#include "Models/UI/Window.h"
#include "TAKEnhancedDll/Settings.hpp"

extern "C" __declspec(dllexport) DWORD setListItem_fcnAddr = 0;
extern "C" __declspec(dllexport) bool TAKisInitialized = false;

Settings settings;
Logger logger;
HANDLE hProcess = NULL;

std::shared_ptr<GameWrapper> gameWrapper;

void initializeContext()
{
    settings.initializeSettings();
    initializeKeys();
    initializeCommands();
    settings.LoadSettings("TAKEnhanced.cfg");

    logger.initialize("TAKEnhancedLog.txt", "a");

    logger.context("DLL");

    baseAddress = getProcessBaseAddress("Kingdoms.icd");
    logger.log("Process base address loaded successfully.");

    hProcess = GetCurrentProcess();
    logger.log("Current process loaded successfully.\n");

    gameWrapper = std::make_shared<GameWrapper>(baseAddress);

    logger.section("CHANGES");

    // Initialize Global Pointers
    uiHandler = (GameInterfaceHandler*) (GlobalPointers::GameInterfaceHandler + baseAddress);

    // Initialize functions
    setListItem_fcnAddr = *(DWORD*) (FunctionsOffsets::changeSelectedItem + baseAddress);
}
