#include "TAKEnhancedDll/Changes/SearchBox.hpp"

#include <conio.h>

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKCore/ModelsExtensions/GadgetExtensions.h"
#include "TAKCore/ModelsExtensions/WindowExtensions.h"

#include "TAKCore/Models/UI/BattleMenu.h"
#include <TAKEnhancedDll/Wrappers/ChooseMapMenuWrapper.h>
#include <TAKEnhancedDll/Wrappers/BattleMenuWrapper.h>
#include <Utils/Console.hpp>

#define VK_BACKSPACE VK_BACK

void TryToInitializeSearchBox();
void InitializeSearchBox(Window* window);

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
