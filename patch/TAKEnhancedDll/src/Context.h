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

#include "Logger.h"
#include "Functions/FunctionsOffsets.h"
#include "GlobalPointers/GlobalPointers.h"
#include "GameFunctions.h"
#include "Settings.h"
#include "Models/Side.h"
#include "./Wrappers/GameWrapper.h"
#include "./Wrappers/MatchWrapper.h"
#include "Models/UI/Window.h"

extern "C" __declspec(dllexport) DWORD setListItem_fcnAddr = 0;

Settings settings;
Logger logger;
HANDLE hProcess = NULL;

GameWrapper game;

Window* GetWindowCurrentWindow()
{
	WindowHandler* windowHandler = uiHandler->windowHandler;

	if (windowHandler == nullptr)
	{
		return nullptr;
	}

	Gadget* focusedGadget = windowHandler->focusedGadget;

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

	mouseHoveredUnitAddress = game.getSelectedUnitAddress();

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
	uiHandler = (GameInterfaceHandler*) (GlobalPointers::GameInterfaceHandler + baseAddress);

	// Initialize functions
	setListItem_fcnAddr = *(DWORD*) (FunctionsOffsets::changeSelectedItem + baseAddress);
}