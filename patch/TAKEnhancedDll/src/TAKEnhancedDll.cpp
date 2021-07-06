#include <Windows.h>

#include <thread>

#include "Changes.h"
#include "./Launcher/main_form.h"
#include "TakEnhancedService.h"

void startConsole();

BOOL WINAPI DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        initializeContext();

        main_form launcher;
        launcher.show();

        if (settings.EnableDevMode) {
            startConsole();
        }

        applyChanges();

        std::thread TAKEnhancedServiceThread(startTAKEnhancedService);
        TAKEnhancedServiceThread.detach();
    }

    return true;
}