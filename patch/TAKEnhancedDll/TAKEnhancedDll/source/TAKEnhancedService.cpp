#include "TAKEnhancedDll/TAKEnhancedService.hpp"
#include "TAKEnhancedDll/Changes/RandomRace.hpp"
#include "TAKEnhancedDll/Changes/OffscreenFix.hpp"
#include "TAKEnhancedDll/Changes/SearchBox.hpp"
#include "TAKEnhancedDll/Commands/Command.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
#include "TAKEnhancedDll/Hooks/LoadingScreenHook.hpp"

#include <iostream>
#include <queue>
#include "ddraw.h"
#include <Utils/Window.hpp>
#include <Utils/Keyboard.hpp>

#pragma comment(lib,"ddraw.lib") 

/*********************************************************
 
    The TA:K Enhanced Service is a service which will 
    be running while the game is running, doing several
    different tasks.

**********************************************************/

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

// Keys that should fire once only
std::vector<int> singleShotKeys = {
    VK_RETURN,
    VK_R,
    VK_S,
    VK_K
};

std::vector<int> specialKeys = { VK_CTRL };

void processInputSequence(std::queue<int>& sequence)
{
    for (KeyBinding keyBinding : userConfig->keyBindings) {
        if (keyBinding.keyCombination.keys.empty())
            continue;

        int i = 0;

        std::queue<int> sequenceCopy = sequence;
        while (!sequenceCopy.empty()) {
            int key = sequenceCopy.front();

            if (keyBinding.keyCombination.keys[i] != key) {
                break;
            }

            sequenceCopy.pop();

            i++;
        }

        if (sequenceCopy.empty()) {
            keyBinding.command.execute();
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

void waitForTheGameToLaunch()
{
    HWND takWindow = nullptr;
    while (takWindow == nullptr) {
        logger->info("Waiting for the game to launch...");
        takWindow = GetThisWindow("Kingdoms");

        Sleep(100);
    }

    logger->info("Game has launched!");
}

void guaranteeFocus() {
    HWND takWindow = GetThisWindow("Kingdoms");

    for (int i = 0; i < 5; i++) {
        SwitchToThisWindow(takWindow, true);
        SetWindowPos(takWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
}

void startTAKEnhancedService(std::shared_ptr<GameConfig> gameConfig)
{
    waitForTheGameToLaunch();
    guaranteeFocus();

    logger->context("TA:K Enhanced Service");
    logger->info("TA:K Enhanced Service started!");

    /*lpDDSurface = &(IDirectDrawSurface*) ;

    uintptr_t* DirectDrawVTable = (uintptr_t*) 0x5066A2A0;


    HookVTable(&DirectDrawVTable, 5, (uintptr_t) &newBlt, oldBlt);*/

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

        if (gameConfig->offscreenFix.enabled) {
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

    logger->stop();
}
