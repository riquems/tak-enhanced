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
void ConfigureConsole(uint height, uint width, HWND zOrder, bool borderless);

extern "C" __declspec(dllexport) bool nameMatches = false;
extern "C" __declspec(dllexport) int itemIndex = 0;
extern "C" __declspec(dllexport) DWORD listBoxAddr = 0;

extern "C" __declspec(dllexport) void __stdcall updateSearchBox()
{
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

void StartSearchBox(std::vector<std::string>* mapNamesLowerCase)
{
    std::string stringToSearchFor("");

    char c;

    bool end = false;
    while (!end)
    {
        if (!_kbhit()) {
            Sleep(100);
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
    WindowHandler* windowHandler = uiHandler->windowHandler;

    if (windowHandler == nullptr) {
        return;
    }

    Gadget* focusedGadget = windowHandler->focusedGadget;

    if (focusedGadget == nullptr) {
        return;
    }

    if (!GadgetExtensions::isListBox(focusedGadget, baseAddress)) {
        return;
    }

    listBoxAddr = (DWORD) focusedGadget;
    Window* gadgetParent = focusedGadget->parent;

    bool isAnyOfTheSupportedMenus = WindowExtensions::isChooseMapMenu(gadgetParent, baseAddress) ||
                                    WindowExtensions::isBattleMenu(gadgetParent, baseAddress);

    if (!isAnyOfTheSupportedMenus) {
        return;
    }

    InitializeSearchBox(gadgetParent);
}

void InitializeSearchBox(Window* window)
{
    StartConsole();
    ConfigureConsole(600, 40, HWND_TOPMOST, true);

    std::cout << "Type the name of the map to search for it, press enter after you're done." << std::endl;
    std::cout << "> ";

    if (WindowExtensions::isChooseMapMenu(window, baseAddress))
    {
        ChooseMapMenu* chooseMapMenu = (ChooseMapMenu*) window;

        ChooseMapMenuWrapper chooseMapMenuWrapper(chooseMapMenu);

        StartSearchBox(&chooseMapMenuWrapper._mapNamesLowerCase);
    }
    else if (WindowExtensions::isBattleMenu(window, baseAddress))
    {
        BattleMenu* battleMenu = (BattleMenu*) window;

        BattleMenuWrapper battleMenuWrapper(battleMenu);

        StartSearchBox(&battleMenuWrapper._mapNamesLowerCase);
    }
}

void ConfigureConsole(uint width, uint height, HWND zOrder, bool borderless)
{
    SetConsoleBufferSize(256, 2);

    RECT desktopWndRect;

    HWND desktopWnd = GetDesktopWindow();

    GetWindowRect(desktopWnd, &desktopWndRect);

    int consoleWidth = width;
    int consoleHeight = height;
    int xConsolePosition;
    int yConsolePosition;

    xConsolePosition = ((desktopWndRect.right - desktopWndRect.left) / 2) - (consoleWidth / 2);

    yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - (consoleHeight / 2);

    if (isFullscreen)
    {
        yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - 385;
    }

    HWND consoleWindow = GetConsoleWindow();

    if (borderless)
        SetWindowLongPtr(consoleWindow, GWL_STYLE, WS_POPUPWINDOW);
    
    // SetWindowPos(consoleWindow, zOrder, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_NOACTIVATE | SWP_NOOWNERZORDER);
    SetWindowPos(consoleWindow, zOrder, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_SHOWWINDOW);
}

void startConsole()
{
    AllocConsole();

    freopen_s((FILE**) stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
    std::cout.clear();
    std::cin.clear();

    ConfigureConsole(600, 200, HWND_NOTOPMOST, false);
}