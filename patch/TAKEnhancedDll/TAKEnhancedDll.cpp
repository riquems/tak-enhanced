#include <Windows.h>

#include <thread>

#include "Changes.h"
#include "main_form.h"
#include "Helper.h"

BOOL WINAPI DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		initializeContext();

		main_form launcher;
		launcher.show();

		applyChanges();

		std::thread takEnhancedServiceThread(TakEnhancedService);
		takEnhancedServiceThread.detach();
	}

	return true;
}