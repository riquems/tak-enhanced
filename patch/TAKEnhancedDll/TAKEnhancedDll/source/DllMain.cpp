#include <Windows.h>
#include <string>

#include "TAKEnhancedDll/App.hpp"

void showMessageBox(std::string message)
{
    MessageBoxA(NULL, message.c_str(), "Teste", MB_OK);
}

BOOL WINAPI DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        init();
    }

    return true;
}
