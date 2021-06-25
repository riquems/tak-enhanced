#pragma once
#include <conio.h>

#include "MemoryHandler.h"
#include "ModelsExtensions/GadgetExtensions.h"
#include "ModelsExtensions/WindowExtensions.h"

#include "../Wrappers/ChooseMapMenuWrapper.h"
#include "../Wrappers/BattleMenuWrapper.h"
#include "Models/UI/BattleMenu.h"

#define VK_BACKSPACE VK_BACK

void TryToInitializeSearchBox();
void InitializeSearchBox(Window* window);
void ConfigureConsole();

extern "C" __declspec(dllexport) bool TAKisInitialized = false;

extern "C" __declspec(dllexport) bool nameMatches = false;
extern "C" __declspec(dllexport) int itemIndex = 0;
extern "C" __declspec(dllexport) DWORD listBoxAddr = 0;

extern "C" __declspec(dllexport) void __stdcall updateSearchBox()
{
	if (!TAKisInitialized)
	{
		TAKisInitialized = true;
	}

	if (listBoxAddr) {
		if (nameMatches) {
			__asm {
				push itemIndex
				mov ecx, listBoxAddr
				call setListItem_fcnAddr
			}

			nameMatches = false;
		}
	}
}

bool str_contains_str(std::string& str1, std::string& str2)
{
	return str1.find(str2) != std::string::npos;
}

void StartSearchBox(ChooseMapMenuWrapper& chooseMapMenuWrapper)
{
	std::string stringToSearchFor("");

	std::vector<std::string>* mapNamesLowerCase = &chooseMapMenuWrapper._mapNamesLowerCase;

	char c;

	bool end = false;
	while (!end)
	{
		if (_kbhit() == 0) {
			Sleep(10);
			continue;
		}

		c = _getch();

		HWND consoleWnd;

		switch (c)
		{
			case VK_BACKSPACE:
				if (!stringToSearchFor.empty()) {
					std::cout << "\b \b";
					stringToSearchFor.pop_back();
				}
				break;
			case '\r':
				consoleWnd = GetConsoleWindow();
				FreeConsole();
				PostMessage(consoleWnd, WM_CLOSE, NULL, NULL);
				end = true;
				break;
			case '?':
				srand(HelperFunctions::GetMilliseconds());
				itemIndex = rand() % mapNamesLowerCase->size();
				nameMatches = true;
				break;
			default:
				stringToSearchFor.push_back(c);
				std::cout << (char) c;
				break;
		}

		if (!stringToSearchFor.empty() && !end)
		{
			std::transform(stringToSearchFor.begin(), stringToSearchFor.end(), stringToSearchFor.begin(),
				[](unsigned char c) { return std::tolower(c); });

			std::vector<std::string>::iterator it;

			it = std::find_if(mapNamesLowerCase->begin(), mapNamesLowerCase->end(),
				[&stringToSearchFor](std::string mapName)
				{
					return str_contains_str(mapName, stringToSearchFor);
				});

			if (it == mapNamesLowerCase->end())
			{
				continue;
			}

			itemIndex = std::distance(mapNamesLowerCase->begin(), it);
			nameMatches = true;
		}
	}
}

void TryToInitializeSearchBox()
{
	MenuHandler* menuHandler = uiHandler->menuHandler;
	if (menuHandler == nullptr)
	{
		return;
	}

	Gadget* focusedGadget = menuHandler->focusedGadget;

	if (focusedGadget == nullptr)
	{
		return;
	}

	if (!GadgetExtensions::isListBox(focusedGadget, baseAddress))
	{
		return;
	}

	listBoxAddr = (DWORD) focusedGadget;
	Window* gadgetParent = focusedGadget->parent;

	bool isSupportedMenus = WindowExtensions::isChooseMapMenu(gadgetParent, baseAddress) ||
					        WindowExtensions::isBattleMenu(gadgetParent, baseAddress);

	if (!isSupportedMenus)
	{
		return;
	}

	InitializeSearchBox(gadgetParent);
}

void InitializeSearchBox(Window* window)
{
	StartConsole();
	ConfigureConsole();

	std::cout << "Type the name of the map to search for it, press enter after you're done." << std::endl;
	std::cout << "> ";

	if (WindowExtensions::isChooseMapMenu(window, baseAddress))
	{
		ChooseMapMenu* chooseMapMenu = (ChooseMapMenu*) window;

		ChooseMapMenuWrapper chooseMapMenuWrapper(chooseMapMenu);
		
		StartSearchBox(chooseMapMenuWrapper);
	}

	/*else if (WindowExtensions::isBattleMenu(window, baseAddress))
	{
		BattleMenu* battleMenu = (BattleMenu*) window;

		BattleMenuWrapper battleMenuWrapper(battleMenu);
	}*/
}

void ConfigureConsole()
{
	SetConsoleBufferSize(256, 2);

	RECT desktopWndRect;

	HWND desktopWnd = GetDesktopWindow();

	GetWindowRect(desktopWnd, &desktopWndRect);

	int consoleWidth = 600;
	int consoleHeight = 40;
	int xConsolePosition;
	int yConsolePosition;

	xConsolePosition = ((desktopWndRect.right - desktopWndRect.left) / 2) - (consoleWidth / 2);

	yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - (consoleHeight / 2);

	if (isFullscreen)
	{
		yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - 385;
	}

	HWND consoleWindow = GetConsoleWindow();

	SetWindowLongPtr(consoleWindow, GWL_STYLE, WS_POPUPWINDOW);
	SetWindowPos(consoleWindow, HWND_TOPMOST, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_SHOWWINDOW);
}