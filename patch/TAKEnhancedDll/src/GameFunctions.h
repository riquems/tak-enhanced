#pragma once
#include "./Context.h"

#include "Windows.h"
#include "GlobalPointers/GlobalPointers.h"
#include "Models/Player.h"
#include "Models/HapiFile.h"

DWORD GetAbsoluteAddress(DWORD);

namespace Game
{
	Player* players;
}

namespace GameFunctionsExtensions
{
	Player* GetPlayers();
	std::vector<HapiFile*> GetLoadedHapiFiles();
}

Player* GameFunctionsExtensions::GetPlayers()
{
	DWORD* gamePtr = (DWORD*) GetAbsoluteAddress(GlobalPointers::ptr_22D55C);

	Player* players = (Player*) (*gamePtr + 0x2404);

	return players;
}

std::vector<HapiFile*> GameFunctionsExtensions::GetLoadedHapiFiles()
{
	std::vector<HapiFile*> hapiFiles;

	DWORD* filesPtr = (DWORD*) GetAbsoluteAddress(GlobalPointers::ptr_241A48);

	DWORD* hpiDirectory = (DWORD*) (*filesPtr + 0x5EA);
	DWORD* hpiFilesPtr = (DWORD*) (*hpiDirectory);
	HapiFile** hpiFiles = (HapiFile**) *hpiFilesPtr;

	HapiFile** nextHapiFile = hpiFiles;

	StartConsole();

	while (*nextHapiFile != nullptr && (*nextHapiFile)->vTable != 0) {
		hapiFiles.push_back(*nextHapiFile);
		std::cout << (*nextHapiFile)->filename << std::endl;
		nextHapiFile++;
	}

	return hapiFiles;
}

