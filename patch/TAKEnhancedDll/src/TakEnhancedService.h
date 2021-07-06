#pragma once
#include "./Changes/HelperFeatures.h"
#include "./Changes/RandomRace.h"
#include "./Changes/OffscreenFix.h"
#include "./Changes/SearchBox.h"
#include "./Changes/BuildingsShortcuts.h"
#include <iostream>
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

    char c;
    while (true) {
        if (settings.OffscreenFix && gameWrapper->match->isRunning()) {
            startOffscreenMonitorThread();
        }
       
        if (gameWrapper->isBuildMenuOpen()) {
            for (std::pair<int, int> keyValue : settings.buildingKeys) {
                if (isKeyDown(keyValue.first)) {
                    gameWrapper->selectBuilding(keyValue.second);
                }
            }

            /*if (isKeyDown(VK_J)) {
                if (i > 2) {
                    i = 0;
                }

                gameWrapper->switchSelectedUnitHumor(i);
                i++;
            }*/
        }

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

        auto singleShotKeysStillBeingHold = [&]()->bool {
            for (int key : singleShotKeys) {
                if (isKeyDown(key)) {
                    return true;
                }
            }

            return false;
        };

        while (singleShotKeysStillBeingHold()) {
            Sleep(10);
        }

        Sleep(10);
    }
}
