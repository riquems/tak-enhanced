#include <Windows.h>
#include <string>

#include "TAKEnhancedDll/App.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

void showMessageBox(std::string message)
{
    MessageBoxA(NULL, message.c_str(), "Teste", MB_OK);
}

BOOL WINAPI DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        init();
        break;
    case DLL_PROCESS_DETACH:
        files::move(exePath, launcherConfig->modsPath, {
            .filenames = &currentGameConfig->mods.selectedMods
        });

        break;
    }

    return true;
}
