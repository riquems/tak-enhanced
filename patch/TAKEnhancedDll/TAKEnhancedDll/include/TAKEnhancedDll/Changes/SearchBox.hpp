#pragma once
#include <conio.h>
#include <TAKEnhancedDll/common.hpp>
#include <TAKCore/Models/UI/Window.h>
#include <IntSafe.h>

#define VK_BACKSPACE VK_BACK

extern "C" __declspec(dllexport) bool needsToUpdateSelectedItem;
extern "C" __declspec(dllexport) int selectedItemIndex;
extern "C" __declspec(dllexport) DWORD listBoxAddr;

extern "C" __declspec(dllexport) void __stdcall updateSearchBox();

void StartSearchBox(std::vector<std::string> maps);

void TryToInitializeSearchBox();

void InitializeSearchBox(Window* window);
