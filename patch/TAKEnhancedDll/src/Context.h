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
#include "UserInterfaceHandler.h"

DWORD baseAddress = 0;
UserInterfaceHandler* uiHandler = nullptr;

#include "Logger.h"
#include "OriginalFunctionsOffsets.h"
#include "GlobalPointers.h"
#include "GameFunctions.h"
#include "Settings.h"
#include "Side.h"
#include "./Wrappers/GameWrapper.h"
#include "./Wrappers/MatchWrapper.h"

extern "C" __declspec(dllexport) DWORD setListItem_fcnAddr = 0;

Settings settings;
Logger logger;
HANDLE hProcess = NULL;

GameWrapper game;

Window* GetWindowCurrentWindow()
{
	MenuHandler* menuHandler = uiHandler->menuHandler;

	if (menuHandler == nullptr)
	{
		return nullptr;
	}

	Gadget* focusedGadget = menuHandler->focusedGadget;

	if (focusedGadget == nullptr)
	{
		return nullptr;
	}

	return focusedGadget->parent;
}

Side* GetSides()
{
	DWORD* gamePtr = (DWORD*) (0x22D55C + baseAddress);
	Side* sides = (Side*) (*gamePtr + 0x3078);

	return sides;
}

int GetNumberOfSides()
{
	DWORD* gamePtr = (DWORD*) (0x22D55C + baseAddress);
	int* numberOfSidesPtr = (int*) (*gamePtr + 0x3074);

	return *numberOfSidesPtr;
}

void PrintMouseHoveredUnitAddress()
{
	DWORD mouseHoveredUnitAddress = 0;

	mouseHoveredUnitAddress = GameFunctions::getMouseHoveredUnitAddress();

	std::cout << std::hex << mouseHoveredUnitAddress << std::endl;
}

DWORD GetAbsoluteAddress(DWORD relativeAddress)
{
	return relativeAddress + baseAddress;
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

	AllocConsole();
	freopen_s((FILE**) stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
	std::cin.get();
}