#include "TAKEnhancedDll/Changes/SearchBox.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

#include <conio.h>

#include "TAKCore/ModelsExtensions/WindowExtensions.h"
#include "TAKCore/ModelsExtensions/GadgetExtensions.h"

#include "TAKCore/Models/UI/BattleMenu.h"
#include <TAKEnhancedDll/Wrappers/ChooseMapMenuWrapper.h>
#include <TAKEnhancedDll/Wrappers/BattleMenuWrapper.h>
#include <Utils/Console.hpp>
#include <Utils/Window.hpp>

#define VK_BACKSPACE VK_BACK

void TryToInitializeSearchBox();
void InitializeSearchBox(Window* window);

extern "C" __declspec(dllexport) bool needsToUpdateSelectedItem = false;
extern "C" __declspec(dllexport) int selectedItemIndex = 0;
extern "C" __declspec(dllexport) DWORD listBoxAddr = 0;

extern "C" __declspec(dllexport) void __stdcall updateSearchBox()
{
    if (listBoxAddr) {
        if (needsToUpdateSelectedItem) {
            __asm {
                push selectedItemIndex
                mov ecx, listBoxAddr
                call setSelectedListItem_fcnAddr
            }

            needsToUpdateSelectedItem = false;
        }
    }
}

void setSelectedItemIndex(int index) {
    selectedItemIndex = index;
    needsToUpdateSelectedItem = true;
}

void goToNextOccurrence(std::string input, const std::vector<std::string>& maps) {
    if (input.empty())
        return;

    logger->debug("Searching for %s...", input.c_str());

    std::transform(input.begin(), input.end(), input.begin(),
        [](unsigned char c) { return std::tolower(c); });

    logger->debug("Search starting at: %s", (maps.begin() + selectedItemIndex + 1)->c_str());

    auto it = std::find_if(
        maps.begin() + selectedItemIndex + 1,
        maps.end(),
        [&](const std::string& map) {
            return str_contains_str(map, input);
        }
    );

    if (it == maps.end()) {
        logger->debug("No more occurrences found.");
        return;
    }

    int nextOccurrenceIndex = std::distance(maps.begin(), it);
    setSelectedItemIndex(nextOccurrenceIndex);
}

void goToPreviousOccurrence(std::string input, const std::vector<std::string>& maps) {
    if (input.empty())
        return;

    logger->debug("Searching for %s...", input.c_str());

    std::transform(input.begin(), input.end(), input.begin(),
        [](unsigned char c) { return std::tolower(c); });

    logger->debug("Search starting at: %s", (maps.rbegin() + (maps.size() - selectedItemIndex))->c_str());

    auto it = std::find_if(
        maps.rbegin() + (maps.size() - selectedItemIndex),
        maps.rend(),
        [&](const std::string& map) {
            return str_contains_str(map, input);
        }
    );

    if (it == maps.rend()) {
        logger->debug("No more occurrences found.");
        return;
    }

    int previousOccurrenceIndex = std::distance(it, maps.rend()) - 1;
    setSelectedItemIndex(previousOccurrenceIndex);
}

void search(std::string input, const std::vector<std::string>& maps) {
    if (input.empty())
        return;

    std::transform(input.begin(), input.end(), input.begin(),
        [](unsigned char c) { return std::tolower(c); });

    auto it = std::find_if(
        maps.begin(),
        maps.end(),
        [&](const std::string& map) {
            return str_contains_str(map, input);
        }
    );

    if (it == maps.end()) {
        return;
    }

    setSelectedItemIndex(std::distance(maps.begin(), it));
}

void StartSearchBox(std::vector<std::string> maps)
{
    std::string input;

    char c;
    int c2;

    bool end = false;
    while (!end)
    {
        if (!_kbhit()) {
            Sleep(10);
            continue;
        }

        c = _getch();

        HWND wnd;

        switch (c)
        {
            case VK_BACKSPACE:
                if (!input.empty()) {
                    std::cout << "\b \b";
                    input.pop_back();

                    search(input, maps);
                }
                break;
            case VK_RETURN:
            case VK_ESCAPE:
                std::cout << std::endl << std::endl;
                ConfigureConsole(600, 300, HWND_TOP, false);
                wnd = GetThisWindow("Kingdoms");
                SetForegroundWindow(wnd);
                end = true;
                break;
            case 0:
                c2 = _getch();

                switch (c2) {
                case 61: // F3
                    goToNextOccurrence(input, maps);
                    break;
                case 86: // SHIFT + F3
                    goToPreviousOccurrence(input, maps);
                    break;
                }

                break;
            case '?':
                srand(HelperFunctions::GetMilliseconds());
                setSelectedItemIndex(rand() % maps.size());
                break;
            default:
                if (c == 0) {
                    break;
                }

                if (59 <= c && c <= 62) {
                    break;
                }

                input.push_back(c);

                std::cout << (char) c;
                if (logger->minimumLevel() == LogLevel::Debug)
                    std::cout << " (" << (int)c << ")";

                search(input, maps);
                break;
        }
    }
}

void TryToInitializeSearchBox()
{
    WindowHandler* windowHandler = uiHandler->windowHandler;

    if (windowHandler == nullptr) {
        return;
    }

    Window* focusedWindow = windowHandler->focusedWindow;

    if (focusedWindow == nullptr) {
        return;
    }

    if (!GadgetExtensions::isListBox(focusedWindow, baseAddress)) {
        return;
    }

    listBoxAddr = (DWORD) focusedWindow;
    Window* gadgetParent = focusedWindow->parent;

    bool isAnyOfTheSupportedMenus = WindowExtensions::isChooseMapMenu(gadgetParent, baseAddress) ||
                                    WindowExtensions::isBattleMenu(gadgetParent, baseAddress);

    if (!isAnyOfTheSupportedMenus) {
        return;
    }

    InitializeSearchBox(gadgetParent);
}

void InitializeSearchBox(Window* window)
{
    HWND kingdoms = FindWindow(NULL, "Kingdoms");
    SetWindowPos(kingdoms, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    HWND console = FindWindow(NULL, "Kingdoms.icd");
    SetForegroundWindow(console);

    ConfigureConsole(600, 300, HWND_TOPMOST, true);

    std::cout << std::endl;
    std::cout << "Start typing the name of the map to search for it." << std::endl;
    std::cout << "Press Esc or Enter after you're done." << std::endl;
    std::cout << "F3 goes to the next occurrence." << std::endl;
    std::cout << "Shift + F3 goes to the previous occurrence." << std::endl;
    std::cout << "Type ? for a random map." << std::endl;
    std::cout << "> ";

    if (WindowExtensions::isChooseMapMenu(window, baseAddress))
    {
        ChooseMapMenu* chooseMapMenu = (ChooseMapMenu*) window;

        ChooseMapMenuWrapper chooseMapMenuWrapper(chooseMapMenu);

        StartSearchBox(chooseMapMenuWrapper.mapNamesLowerCase);
    }
    else if (WindowExtensions::isBattleMenu(window, baseAddress))
    {
        BattleMenu* battleMenu = (BattleMenu*) window;

        BattleMenuWrapper battleMenuWrapper(battleMenu);

        StartSearchBox(battleMenuWrapper.mapNamesLowerCase);
    }
}
