#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <chrono>

DWORD getProcessId(std::string processName)
{
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(processesSnapshot, &processEntry) == FALSE) {
		CloseHandle(processesSnapshot);
		return 0;
	}

	do {
		//char processNameBuffer[FILENAME_MAX];
		//wcstombs_s(NULL, processNameBuffer, FILENAME_MAX, processEntry.szExeFile, sizeof(processEntry.szExeFile));

		if (processName.compare(processEntry.szExeFile) == 0) {
			CloseHandle(processesSnapshot);
			return processEntry.th32ProcessID;
		}

	} while (Process32Next(processesSnapshot, &processEntry));

	CloseHandle(processesSnapshot);
	return 0;
}

DWORD getProcessBaseAddress(std::string processName)
{
	DWORD processId = getProcessId(processName);
	HANDLE modulesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	MODULEENTRY32 moduleEntry;
	moduleEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(modulesSnapshot, &moduleEntry) == FALSE) {
		CloseHandle(modulesSnapshot);
		return 0;
	}

	do {
		if (processName.compare(moduleEntry.szModule) == 0) {
			CloseHandle(modulesSnapshot);
			return (DWORD) moduleEntry.modBaseAddr;
		}

	} while (Module32Next(modulesSnapshot, &moduleEntry));

	CloseHandle(modulesSnapshot);
	return 0;
}

bool isKeyDown(int keyCode)
{
	return GetAsyncKeyState(keyCode) & 0x8000;
}

void StartConsole()
{
	AllocConsole();
	freopen_s((FILE**) stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
}

void SetConsoleBufferSize(SHORT x, SHORT y)
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSBSize;
	NewSBSize.X = x;
	NewSBSize.Y = y;

	SetConsoleScreenBufferSize(hOut, NewSBSize);
}

namespace HelperFunctions
{
	long long GetMilliseconds()
	{
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
		return ms.count();
	}
}

void toggleBoolean(bool& boolean)
{
	boolean = !boolean;
}

bool str_equals_str(const char* str1, const char* str2)
{
	return strcmp(str1, str2) == 0;
}

const char* boolean_to_str(bool& boolean)
{
	return boolean ? "true" : "false";
}

bool str_to_boolean(const char* str)
{
	return (str_equals_str(str, "true")) ? true : false;
}

unsigned int str_to_uint(const char* str)
{
	return strtoul(str, nullptr, 0);
}

/*DWORD GetMainThreadId() {
	const std::tr1::shared_ptr<void> hThreadSnapshot(
		CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0), CloseHandle);
	if (hThreadSnapshot.get() == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("GetMainThreadId failed");
	}
	THREADENTRY32 tEntry;
	tEntry.dwSize = sizeof(THREADENTRY32);
	DWORD result = 0;
	DWORD currentPID = GetCurrentProcessId();
	for (BOOL success = Thread32First(hThreadSnapshot.get(), &tEntry);
		!result && success && GetLastError() != ERROR_NO_MORE_FILES;
		success = Thread32Next(hThreadSnapshot.get(), &tEntry))
	{
		if (tEntry.th32OwnerProcessID == currentPID) {
			result = tEntry.th32ThreadID;
		}
	}
	return result;
}*/