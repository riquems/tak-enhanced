#include "TAKEnhancedDll/common.hpp"
#include "TAKEnhancedDll/TAKEnhancedService.hpp"
#include "TAKEnhancedDll/Changes/RandomRace.hpp"
#include "TAKEnhancedDll/Changes/OffscreenFix.hpp"
#include "TAKEnhancedDll/Changes/SearchBox.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedDll/Hooks/LoadingScreenHook.hpp"
#include "TAKEnhancedDll/Commands/ExecuteCommand.hpp"

#include <iostream>
#include "ddraw.h"
#include <Utils/Window.hpp>
#include <Utils/Keyboard.hpp>
#include <Utils/HelperFunctions.hpp>
#include <TAKCore/Commands.h>
#include <TAKCore/Functions/Functions.h>
#include <Utils/Timer.hpp>
#include <thread>
#include <TAKEnhancedLibrary/State.hpp>
#include <TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp>
#include <TAKEnhancedLibrary/Commands/Commands.hpp>
#include <TAKEnhancedLibrary/Keys/KeyComparator.hpp>
#include "TAKEnhancedLibrary/Units/Units.hpp"
#include "TAKEnhancedLibrary/Match/Match.hpp"
#include "TAKEnhancedLibrary/Graphics/Graphics.hpp"

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

bool keyCombinationMatch(const KeyCombination& keyCombination, std::vector<short> pressedKeys) {
    if (keyCombination.keys.empty())
        return false;

    for (auto& pressedKey : pressedKeys) {
        bool contains = dky::contains(keyCombination.keys,
            [&](const Key& key) {
                return KeyComparator::isLike(key, pressedKey);
            }
        );

        if (!contains)
            return false;
    }

    for (auto& key : keyCombination.keys) {
        bool contains = dky::contains(pressedKeys,
            [&](const short& pressedKey) {
                return KeyComparator::isLike(key, pressedKey);
            }
        );

        if (!contains)
            return false;
    }

    return true;
}

void handleInputs(KeyboardState& keyboardState)
{
    auto pressedKeysMap = dky::unordered_map::filter(keyboardState.keys,
        [](std::pair<short, KeyState> entry)->bool {
            return entry.second == KeyState::JustPressed || entry.second == KeyState::Pressed;
        }
    );

    auto pressedKeys = dky::map(
        std::vector<std::pair<short, KeyState>>(pressedKeysMap.begin(), pressedKeysMap.end()),
        [](const std::pair<short, KeyState>& elem) {
            return elem.first;
        }
    );

    if (pressedKeys.empty())
        return;

    json j = pressedKeys;
    logger->debug("Pressed keys: %s", j.dump().c_str());

    for (const KeyBinding& keyBinding : userConfig->keyBindings) {
        if (!keyCombinationMatch(keyBinding.keyCombination, pressedKeys))
            continue;

        executeCommand(*keyBinding.command);
    }

    // todo: map all of them as commands

    if (keyCombinationMatch({ Keys::Ctrl, Keys::H }, pressedKeys)) {
        if (!TAKEnhancedLibrary::MatchIsRunning()) {
            logger->debug("Not executing, Match is not running.");
            return;
        }

        auto unit = TAKEnhancedLibrary::GetMouseHoveredUnit();

        if (unit) {
            std::cout << std::hex << unit->raw << std::endl;
        }
    }

    if (keyCombinationMatch({ Keys::Ctrl, Keys::S }, pressedKeys)) {
        if (!TAKEnhancedLibrary::MatchIsRunning()) {
            logger->debug("Not executing, Match is not running.");
            return;
        }

        auto selectedUnits = TAKEnhancedLibrary::GetSelectedUnits();

        if (!selectedUnits.empty()) {
            auto msg = std::accumulate(
                selectedUnits.begin(),
                selectedUnits.end(),
                std::string("Selected Units: "),
                [&](std::string prev, std::shared_ptr<TAKEnhancedLibrary::Unit> next) {
                    return prev + next->name() + (next != *(selectedUnits.end() - 1) ? ", " : ".");
                }
            );

            logger->debug("%s", msg.c_str());
        }
        else {
            logger->debug("There are no selected units");
        }
    }

    if (keyCombinationMatch({ Keys::Ctrl, Keys::F }, pressedKeys)) {
        std::thread t([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            TryToInitializeSearchBox();
        });
        t.detach();
    }

    if (keyCombinationMatch({ Keys::Ctrl, Keys::R }, pressedKeys)) {
        TryToChooseRandomRace();
    }

    if (keyCombinationMatch({ Keys::Ctrl, Keys::K }, pressedKeys)) {
        // ToggleSelectedUnitAura();
    }

    if (keyCombinationMatch({ Keys::Alt, Keys::Return }, pressedKeys)) {
        ToggleFullscreen();
    }
}

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

void bindWndProc();

typedef LRESULT(__stdcall *wndProc_t)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
wndProc_t oldWndProc;
bool bindingScheduled = false;
Timer timer;
KeyboardState state;

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input#keystroke-message-flags
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        {
            WORD vkCode = LOWORD(wParam);                                 // virtual-key code

            WORD keyFlags = HIWORD(lParam);

            WORD scanCode = LOBYTE(keyFlags);                             // scan code
            BOOL isExtendedKey = (keyFlags & KF_EXTENDED) == KF_EXTENDED; // extended-key flag, 1 if scancode has 0xE0 prefix

            if (isExtendedKey)
                scanCode = MAKEWORD(scanCode, 0xE0);

            BOOL wasKeyDown = (keyFlags & KF_REPEAT) == KF_REPEAT;        // previous key-state flag, 1 on autorepeat
            WORD repeatCount = LOWORD(lParam);                            // repeat count, > 0 if several keydown messages was combined into one message

            BOOL isKeyReleased = (keyFlags & KF_UP) == KF_UP;             // transition-state flag, 1 on keyup

            // if we want to distinguish these keys:
            switch (vkCode)
            {
            case VK_SHIFT:   // converts to VK_LSHIFT or VK_RSHIFT
            case VK_CONTROL: // converts to VK_LCONTROL or VK_RCONTROL
            case VK_MENU:    // converts to VK_LMENU or VK_RMENU
                vkCode = LOWORD(MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX));
                break;
            }

            if (vkCode == VK_SPACE) {
                logger->debug("Spacebar pressed");
                TAKEnhancedLibrary::ExecuteCommand(userConfig->onSpacebar);
            }

            if (!isKeyReleased) {
                if (wasKeyDown) {
                    state.keys[vkCode] = KeyState::Pressed;
                }
                else {
                    state.keys[vkCode] = KeyState::JustPressed;
                }
            }
            else {
                state.keys[vkCode] = KeyState::Released;
            }

            handleInputs(state);

            break;
        }
        case WM_LBUTTONDOWN: {
            auto doubleClickTimeInMilliseconds = timer.timeInMilliseconds();

            if (doubleClickTimeInMilliseconds != 0 && doubleClickTimeInMilliseconds <= GetDoubleClickTime()) {
                timer.stop();
                logger->debug("A Triple Click has occured.");
                
                TAKEnhancedLibrary::ExecuteCommand(userConfig->onTripleClick);
            }

            break;
        }
        case WM_LBUTTONDBLCLK: {
            if (wParam & MK_CONTROL) {
                logger->debug("A CTRL + Double Click has occured.");

                TAKEnhancedLibrary::ExecuteCommand(userConfig->onCtrlDoubleClick);
                break;
            }

            logger->debug("A Double Click has occured.");

            TAKEnhancedLibrary::ExecuteCommand(userConfig->onDoubleClick);
            timer.start();

            break;
        }
        case WM_MOUSEWHEEL: {
            short keys = GET_KEYSTATE_WPARAM(wParam);
            short delta = GET_WHEEL_DELTA_WPARAM(wParam);

            auto& orientation = delta > 0 ? RotateOrientation::CounterClockwise : RotateOrientation::Clockwise;

            if (keys & MK_CONTROL) {
                executeCommand(RotateBuildingCommand(
                    RotateBuildingCommandParams {
                        .orientation = orientation,
                        .step = 90
                    }
                ));
            }
            else {
                executeCommand(RotateBuildingCommand(
                    RotateBuildingCommandParams{
                        .orientation = orientation,
                        .step = 5
                    }
                ));
            }

            break;
        }
        case WM_STYLECHANGED:
            logger->debug("[Windows] WM_STYLECHANGED");

            if (!bindingScheduled) {
                bindingScheduled = true;
                std::thread t([&]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    // we need to rebind these because DXWnd overwrites it when this event occurs
                    bindWndProc();

                    bindingScheduled = false;
                });
                t.detach();
            }
            break;
    }

    return oldWndProc(hwnd, msg, wParam, lParam);
}

void bindWndProc() {
    logger->debug("Binding WndProc...");
    auto wnd = GetThisWindow("Kingdoms");
    oldWndProc = (wndProc_t)GetWindowLongPtr(wnd, GWLP_WNDPROC);
    SetWindowLongPtr(wnd, GWLP_WNDPROC, (LONG_PTR)MyWndProc);
}

void startTAKEnhancedService(std::shared_ptr<GameConfig> gameConfig)
{
    waitForTheGameToLaunch();
    guaranteeFocus();

    bindWndProc();

    TAK::init(baseAddress);
    TAKEnhancedLibrary::init(logger);

    logger->context("TA:K Enhanced Service");
    logger->info("TA:K Enhanced Service started!");

    /*lpDDSurface = &(IDirectDrawSurface*) ;

    uintptr_t* DirectDrawVTable = (uintptr_t*) 0x5066A2A0;

    HookVTable(&DirectDrawVTable, 5, (uintptr_t) &newBlt, oldBlt);*/

    bool onFirstGameLoading = false;

    bool matchIsRunning = false;
    bool previousMatchIsRunning = false;
    bool previousInLoadingScreen = false;

    bool hasTriggeredOnFirstGameLoading = false;
    bool hasTriggeredOnInitialize = false;

    while (true) {
        if (!onFirstGameLoading && inLoadingScreen) {
            onFirstGameLoading = true;
            logger->info("[Event] OnFirstGameLoading");

            if (currentGameConfig->developerMode.enabled) {
                logger->info("Activating developer mode");
                gameWrapper->activateDeveloperMode();
            }

            TAKEnhancedLibrary::hpBarRenderer->init();
        }
        
        if (!previousInLoadingScreen && inLoadingScreen) {
            logger->info("[Event] Match has started!");
        }

        previousInLoadingScreen = inLoadingScreen;

        if (!hasTriggeredOnInitialize && TAKisInitialized) {
            hasTriggeredOnInitialize = true;
            gameWrapper->onInitialize();
        }

        if (gameConfig->offscreenFix.enabled) {
            if (!offscreenMonitorThreadRunning && TAKEnhancedLibrary::MatchIsRunning()) {
                startOffscreenMonitorThread();
            }
        }

        Sleep(10);
    }

    logger->stop();
}
