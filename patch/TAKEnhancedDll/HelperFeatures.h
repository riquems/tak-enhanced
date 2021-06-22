#pragma once
#include "Context.h"
#include "Side.h"

extern "C" bool isFullscreen = false;

void ToggleFullscreen()
{
	HWND handle = FindWindowA(NULL, "Kingdoms");

	if (!isFullscreen)
	{
		RECT desktopWndRect;

		HWND desktopWnd = GetDesktopWindow();

		GetWindowRect(desktopWnd, &desktopWndRect);

		int width = desktopWndRect.right;
		int height = desktopWndRect.bottom;

		SetWindowPos(handle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

		isFullscreen = true;
	}
	else {
		int width = 640;
		int height = 480;

		SetWindowPos(handle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

		isFullscreen = false;
	}
}

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