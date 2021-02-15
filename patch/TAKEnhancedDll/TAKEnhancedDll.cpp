#include <Windows.h>

#include <thread>

#include "Changes.h"
#include "Launcher.h"
#include "Helper.h"

BOOL WINAPI DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		initializeContext();

		Launcher launcher;
		launcher.execute();

		applyChanges();

		std::thread helperThread(initializeHelper);
		helperThread.detach();
	}

	return true;
}