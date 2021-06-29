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

		startConsole();

		main_form launcher;
		launcher.show();

		applyChanges();

		std::thread takEnhancedServiceThread(startTakEnhancedService);
		takEnhancedServiceThread.detach();
	}

	return true;
}

void startConsole()
{
	AllocConsole();
	freopen_s((FILE**) stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
}