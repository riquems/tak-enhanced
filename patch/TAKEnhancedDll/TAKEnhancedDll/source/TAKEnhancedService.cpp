#include "TAKEnhancedDll/common.hpp"
#include "TAKEnhancedDll/TAKEnhancedService.hpp"
#include "TAKEnhancedDll/Changes/RandomRace.hpp"
#include "TAKEnhancedDll/Changes/OffscreenFix.hpp"
#include "TAKEnhancedDll/Changes/SearchBox.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
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
#include <TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp>
#include <TAKEnhancedLibrary/Keys/KeyComparator.hpp>
#include "TAKEnhancedLibrary/Units/Units.hpp"
#include "TAKEnhancedLibrary/Graphics/Graphics.hpp"

using namespace TAKEnhancedLibrary;

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

bool keybindingMatch(const KeyBinding& keyBinding, std::vector<short> pressedKeys) {
    if (keyBinding.keyCombination.keys.empty())
        return false;

    for (auto& pressedKey : pressedKeys) {
        bool contains = dky::contains(keyBinding.keyCombination.keys,
            [&](const Key& key) {
                return KeyComparator::isLike(key, pressedKey);
            }
        );

        if (!contains)
            return false;
    }

    for (auto& key : keyBinding.keyCombination.keys) {
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

    /*json j = pressedKeys;
    logger->debug("Pressed keys: %s", j.dump().c_str());*/

    for (const KeyBinding& keyBinding : userConfig->keyBindings) {
        if (!keybindingMatch(keyBinding, pressedKeys))
            continue;

        executeCommand(*keyBinding.command);
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

void bindWndProc();
void executeCommand(std::string command);

typedef LRESULT(__stdcall *wndProc_t)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
wndProc_t oldWndProc;
bool bindingScheduled = false;
Timer timer;

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_KEYDOWN:
            if (wParam == VK_SPACE) {
                logger->debug("Spacebar pressed");
                executeCommand(userConfig->onSpacebar);
            }
        break;
        case WM_LBUTTONDOWN: {
            auto doubleClickTimeInMilliseconds = timer.timeInMilliseconds();

            if (doubleClickTimeInMilliseconds != 0 && doubleClickTimeInMilliseconds <= GetDoubleClickTime()) {
                timer.stop();
                logger->debug("A Triple Click has occured.");
                
                executeCommand(userConfig->onTripleClick);
            }

            break;
        }
        case WM_LBUTTONDBLCLK: {
            if (wParam & MK_CONTROL) {
                logger->debug("A CTRL + Double Click has occured.");

                executeCommand(userConfig->onCtrlDoubleClick);
                break;
            }

            logger->debug("A Double Click has occured.");

            executeCommand(userConfig->onDoubleClick);
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

void executeCommand(std::string command) {
    bool isTargetCommand = dky::contains(
        TAK::Commands::targetCommands,
        [&](const std::string& cmd) {
            return cmd == command;
        }
    );

    if (isTargetCommand) {
        if (!gameWrapper->match->isRunning() || TAKEnhancedLibrary::GetMouseHoveredUnit() == nullptr) {
            logger->debug("Command is a target command and no unit is targetted at the moment. Skipping.");
            return;
        }
    }
    
    logger->debug("Executing command %s", command.c_str());

    if (command == TAK::Commands::DoNothing)
        return;

    TAK::Functions::executeCommand(command.c_str(), false);
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
            if (!offscreenMonitorThreadRunning && gameWrapper->match->isRunning()) {
                startOffscreenMonitorThread();
            }
        }

        if (isKeyDown(VK_CONTROL)) {
            if (isKeyDown(VK_H)) {
                auto unit = TAKEnhancedLibrary::GetMouseHoveredUnit();
                
                if (unit) {
                    std::cout << std::hex << unit->raw << std::endl;
                }
            }
            else if (isKeyDown(VK_S)) {
                auto selectedUnits = TAKEnhancedLibrary::GetSelectedUnits();

                if (!selectedUnits.empty()) {
                    auto msg = std::accumulate(
                        selectedUnits.begin(),
                        selectedUnits.end(),
                        std::string("Selected Units: "),
                        [&](std::string prev, std::shared_ptr<Unit> next) {
                            return prev + next->name() + (next != *(selectedUnits.end() - 1) ? ", " : ".");
                        }
                    );

                    logger->debug("%s", msg.c_str());
                }
                else {
                    logger->debug("There are no selected units");
                }
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

        auto kbState = MyGetKeyboardState();

        handleInputs(*kbState);

        Sleep(10);
    }

    logger->stop();
}
