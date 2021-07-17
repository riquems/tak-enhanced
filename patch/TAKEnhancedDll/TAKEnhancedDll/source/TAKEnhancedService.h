#pragma once
#include "./Changes/HelperFeatures.h"
#include "./Changes/RandomRace.h"
#include "./Changes/OffscreenFix.h"
#include "./Changes/SearchBox.h"
#include "./Changes/BuildingsShortcuts.h"
#include "TAKEnhancedDll/Models/Command.hpp"
#include "CommandsFunctions.h"

#include <iostream>
#include <queue>
#include "ddraw.h"

#pragma comment(lib,"ddraw.lib") 

/*********************************************************
 
    The TA:K Enhanced Service is a service which will 
    be running while the game is running, doing several
    different tasks.

**********************************************************/

// Keys that should fire once only
std::vector<int> singleShotKeys = { VK_RETURN,
                                    VK_R,
                                    VK_S,
                                    VK_K };

void selectBuilding(std::vector<std::string> params)
{
    if (!gameWrapper->isBuildMenuOpen())
        return;

    if (params.size() != 1) {
        logger.log("The number of given parameters is not supported by this command.\n \
                    Command: %s                                                     \n \
                    Number of supported params: 1                                   \n \
                    Number of given params: %d", "Select Building", params.size());
        return;
    }

    int buildingId = std::stoi(params[0]);

    gameWrapper->selectBuilding(buildingId);
}

//typedef HRESULT(__stdcall* BltFcn)(LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDBLTFX);
//
//__declspec(dllexport) BltFcn oldBlt;
//
//__declspec(dllexport) HDC hdc;
//
//__declspec(dllexport) IDirectDrawSurface* lpDDSurface = NULL;
//
//__declspec(dllexport) void DrawTextScreen(const char* text, int x, int y, DWORD Color)
//{
//    int oBkMode = GetBkMode(hdc);
//    int oTextColor = GetTextColor(hdc);
//
//    SetBkMode(hdc, TRANSPARENT);
//    SetTextColor(hdc, Color);
//    TextOut(hdc, x, y, text, lstrlen(text));
//
//    SetBkMode(hdc, oBkMode);
//    SetTextColor(hdc, oTextColor); //Not sure how necessary this is.
//}
//
//HRESULT __stdcall newBlt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
//{
//    if (lpDDSurface->GetDC(&hdc) == DD_OK)
//    {
//        DrawTextScreen("Hello world!", 10, 10, RGB(255, 255, 255));
//        lpDDSurface->ReleaseDC(hdc);
//    }
//
//    return oldBlt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
//}
//
//void HookVTable(uintptr_t** vTable, int targetFcnIndex, uintptr_t newFunction, BltFcn& oldFunction)
//{
//    oldFunction = (BltFcn) (*vTable)[targetFcnIndex];
//    (*vTable)[targetFcnIndex] = newFunction;
//}


void processInputSequence(std::queue<int>& sequence)
{
    for (std::pair<Keys, Command> keyBinding : settings.keyBindings) {
        int i = 0;

        std::queue<int> sequenceCopy = sequence;
        while (!sequenceCopy.empty()) {
            int key = sequenceCopy.front();

            if (keyBinding.first.values[i] != key) {
                break;
            }

            sequenceCopy.pop();

            i++;
        }

        if (sequenceCopy.empty()) {
            keyBinding.second.execute();
        }
    }

    while (!sequence.empty()) {
        sequence.pop();
    }
}

auto singleShotKeysStillBeingHold = [&]()->bool {
    for (int key : singleShotKeys) {
        if (isKeyDown(key)) {
            return true;
        }
    }

    return false;
};



void startTAKEnhancedService()
{
    int i = 0;

    Sleep(1000);

    /*lpDDSurface = &(IDirectDrawSurface*) ;

    uintptr_t* DirectDrawVTable = (uintptr_t*) 0x5066A2A0;


    HookVTable(&DirectDrawVTable, 5, (uintptr_t) &newBlt, oldBlt);*/

    HWND nextWindow = FindWindowA(NULL, "Kingdoms");
    HWND takWindow = nullptr;

    DWORD processId;
    while (nextWindow != NULL) {
        GetWindowThreadProcessId(nextWindow, &processId);

        if (processId == GetCurrentProcessId()) {
            takWindow = nextWindow;
            break;
        }

        nextWindow = FindWindowExA(NULL, nextWindow, NULL, "Kingdoms");
    }

    SwitchToThisWindow(takWindow, true);
    SetWindowPos(takWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

    std::vector<int> specialKeys = { VK_CTRL };

    auto selectBuildingMap =
        std::pair<CommandCode, std::function<void(std::vector<std::string>)>>(CommandCode::SELECT_BUILDING, selectBuilding);

    commandCodeToFunction.insert(selectBuildingMap);

    bool offscreenMonitorThreadRunning = false;

    bool hasTriggeredOnFirstGameLoading = false;
    bool hasTriggeredOnInitialize = false;

    int keyCode;
    while (true) {
        if (!hasTriggeredOnFirstGameLoading && firstLoad) {
            hasTriggeredOnFirstGameLoading = true;
            gameWrapper->onFirstGameLoading();
        }

        if (!hasTriggeredOnInitialize && TAKisInitialized) {
            hasTriggeredOnInitialize = true;
            gameWrapper->onInitialize();
        }

        if (settings.OffscreenFix) {
            if (!offscreenMonitorThreadRunning && gameWrapper->match->isRunning()) {
                startOffscreenMonitorThread();
                offscreenMonitorThreadRunning = true;
            }
        }
        
        // if (!game->typing_state())

        std::queue<int> sequence;

        /*auto specialKeysHit = [&]()->std::pair<bool, int> {
            for (int specialKey : specialKeys) {
                if (GetAsyncKeyState(specialKey) & 0x8000) {
                    return std::pair<bool, int>(true, specialKey);
                }
            }
            
            return std::pair<bool, int>(false, -1);
        }();

        bool specialKeyWasHit = specialKeysHit.first;

        if (specialKeyWasHit) {
            sequence.push(specialKeysHit.second);
        }*/

        if (isKeyDown(VK_CONTROL)) {
            if (isKeyDown(VK_S)) {
                uintptr_t unitAddress = gameWrapper->getMouseHoveredUnitAddress();
                std::cout << std::hex << unitAddress << std::endl;
            }
            else if (isKeyDown(VK_F)) {
                TryToInitializeSearchBox();
            }
            else if (isKeyDown(VK_R)) {
                TryToChooseRandomRace();
            }
            else if (isKeyDown(VK_K)) {
                // ToggleSelectedUnitAura();
            }
        }

        if (isKeyDown(VK_MENU)) {
            if (isKeyDown(VK_RETURN)) {
                ToggleFullscreen();
            }
        }

        while (singleShotKeysStillBeingHold()) {
            Sleep(10);
        }


        keyCode = _mykbhit();
        
        if (!keyCode) {
            Sleep(10);
            continue;
        }

        sequence.push(keyCode);

        processInputSequence(sequence);


        /*if (isKeyDown(VK_J)) {
            if (i > 2) {
                i = 0;
            }

            gameWrapper->switchSelectedUnitHumor(i);
            i++;
        }*/

        Sleep(10);
    }
}
