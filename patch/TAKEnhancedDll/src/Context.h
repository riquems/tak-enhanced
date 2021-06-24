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

#include "Logger.h"
#include "./Wrappers/Info.h"
#include "OriginalFunctionsOffsets.h"
#include "UserInterfaceHandler.h"
#include "GlobalPointers.h"
#include "GameFunctions.h"
#include "Settings.h"
#include "./Wrappers/PlayerWrapper.h"
#include "./Wrappers/MatchWrapper.h"

extern "C" __declspec(dllexport) bool match_has_started = false;

// Is true when "VICTORY" or "DEFEAT" appears on the screen
extern "C" __declspec(dllexport) bool match_has_finished = false;

extern "C" __declspec(dllexport) DWORD setListItem_fcnAddr = 0;
UserInterfaceHandler* uiHandler = nullptr;

Settings settings;
Logger logger;
DWORD baseAddress = 0;
HANDLE hProcess = NULL;

MatchWrapper match_wrapper;

bool playersInitialized = false;
std::vector<PlayerWrapper> players_wrappers;

void InitializePlayersWrappers()
{
	Player* players = GameFunctionsExtensions::GetPlayers();

	Player* nextPlayer = players;
	while (nextPlayer->initialized)
	{
		PlayerWrapper playerWrapper(nextPlayer);

		players_wrappers.push_back(playerWrapper);
		nextPlayer++;
	}
}

void initializeContext()
{
	settings.LoadSettings("TAKEnhanced.cfg");
	logger.initialize("TAKEnhancedLog.txt", "a");

	logger.context("DLL");

	baseAddress = getProcessBaseAddress("Kingdoms.icd");
	logger.log("Process base address loaded successfully.");

	hProcess = GetCurrentProcess();
	logger.log("Current process loaded successfully.\n");

	logger.section("CHANGES");

	// Initialize Global Pointers
	uiHandler = (UserInterfaceHandler*) (GlobalPointers::UserInterfaceHandler + baseAddress);

	// Initialize functions
	GameFunctions::getMouseHoveredUnitAddress = (DWORD(*)()) (FunctionsOffsets::getMouseHoveredUnitAddress + baseAddress);
	setListItem_fcnAddr = *(DWORD*) (FunctionsOffsets::changeSelectedItem + baseAddress);

	//AllocConsole();
	//freopen_s((FILE**) stdin, "CONIN$", "r", stdin);
	//freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
	//std::cout.clear();
	//std::cin.clear();
	//std::cin.get();
}