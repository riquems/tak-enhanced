#pragma once
#include "Utils/HelperFunctions.hpp"

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
        std::chrono::system_clock::duration time_since_epoch = std::chrono::system_clock::now().time_since_epoch();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch);
        return ms.count();
    }
}

void toggleBoolean(bool& boolean)
{
    boolean = !boolean;
}

bool str_contains_str(const std::string& str1, const std::string& str2)
{
    return str1.find(str2) != std::string::npos;
}

bool str_equals_str(const char* str1, const char* str2)
{
    return strcmp(str1, str2) == 0;
}

bool str_equals_str(std::string& str1, std::string& str2)
{
    return str1.compare(str2) == 0;
}

bool str_equals_str(std::string& str1, const std::string& str2)
{
    return str1.compare(str2) == 0;
}

bool str_equals_str(const std::string& str1, const std::string& str2)
{
    return str1.compare(str2) == 0;
}

const char* boolean_to_str(bool& boolean)
{
    return boolean ? "true" : "false";
}

bool str_to_boolean(const char* str)
{
    return (str_equals_str(str, "true")) ? true : false;
}

bool str_to_boolean(std::string str)
{
    return (str_equals_str(str, "true")) ? true : false;
}

unsigned int str_to_uint(const char* str)
{
    return strtoul(str, nullptr, 0);
}

unsigned int str_to_uint(std::string str)
{
    return strtoul(str.c_str(), nullptr, 0);
}

bool vector_has_str(std::vector<std::string>& vector, std::string str)
{
    std::vector<std::string>::iterator it;

    it = std::find_if(vector.begin(), vector.end(),
        [&](std::string vector_str) {
            return str_equals_str(str.c_str(), vector_str.c_str());
        }
    );

    if (it != vector.end()) {
        return true;
    }

    return false;
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

std::vector<std::string> split_str(const char* str, const char* token)
{
    std::vector<std::string> splitted_str;

    char buffer[512];
    strncpy(buffer, str, sizeof(buffer) - 1);

    char* nextElem = strtok(buffer, token);

    while (nextElem != NULL) {
        splitted_str.push_back(std::string(nextElem));

        nextElem = strtok(NULL, token);
    }

    return splitted_str;
}

std::vector<std::string> split_str(std::string str, const char* token)
{
    return split_str(str.c_str(), token);
}
