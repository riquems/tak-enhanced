#include <Windows.h>

#include <thread>

#include "Changes.h"
#include "./Launcher/main_form.h"
#include "TakEnhancedService.h"

BOOL WINAPI DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		initializeContext();

		main_form launcher;
		launcher.show();

		applyChanges();

		std::thread takEnhancedServiceThread(startTakEnhancedService);
		takEnhancedServiceThread.detach();
	}

	return true;
}