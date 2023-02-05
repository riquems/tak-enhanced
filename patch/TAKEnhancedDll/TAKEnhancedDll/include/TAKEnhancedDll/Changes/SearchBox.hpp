#pragma once
#include <conio.h>
#include <TAKEnhancedDll/common.hpp>
#include <TAKEnhancedDll/Memory/MemoryHandler.hpp>
#include <TAKCore/Models/UI/Window.h>

#define VK_BACKSPACE VK_BACK

extern "C" __declspec(dllexport) bool nameMatches;
extern "C" __declspec(dllexport) int itemIndex;
extern "C" __declspec(dllexport) DWORD listBoxAddr;

extern "C" __declspec(dllexport) void __stdcall updateSearchBox();

void StartSearchBox(std::vector<std::string>* mapNamesLowerCase);

void TryToInitializeSearchBox();

void InitializeSearchBox(Window* window);
