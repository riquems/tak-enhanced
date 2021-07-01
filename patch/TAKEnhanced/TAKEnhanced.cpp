#include <string>
#include <fstream>
#include <iostream>

#include "Logger.h"
#include "JunkCode.h"

Logger logger("TAKEnhancedLog.txt", "w");
std::string targetFileName("Kingdoms.icd");
std::string dllFileName("TAKEnhanced.dll");

int make_TAK_inject_ETAK()
{
    std::fstream takexe(targetFileName);

    if (takexe.is_open()) {
        takexe.seekp(0x2271C5);

        takexe.write("TAKEnhanced", 12);

        takexe.seekp(0x227264);

        takexe.write("TAKEnhanced", 12);
    }
    else {
        takexe.close();
        return -1;
    }

    takexe.close();
    return 1;
}

int EnableCommandLineParams()
{
    std::fstream takexe(targetFileName);

    if (takexe.is_open()) {
        takexe.seekg(0x202440);

        if (takexe.get() == 'W') {
            takexe.seekp(0x202440);
            takexe.put('A');
        }
        else {
            return 0;
        }
    }
    else {
        takexe.close();
        return -1;
    }

    takexe.close();
    return 1;
}

BOOL WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    logger.context("EXE");
    quaxkru junkcode;
    STARTUPINFOA startupInfo = {};
    PROCESS_INFORMATION procInfo;

    logger.section("PREPARATION");

    //make_TAK_inject_ETAK();

    quaxkru junkcode2;
    int status = EnableCommandLineParams();

    if (status == -1) {
        logger.error("Couldn't open target file %s.", targetFileName.c_str());
        return false;
    }
    else if (status == 0) {
        logger.log("Command line params are already enabled.");
    }
    else {
        logger.log("Command line params enabled.");
    }

    quaxkru junkcode3;

    char cmdLine[256];

    strcpy(cmdLine, targetFileName.c_str());
    strcat(cmdLine, " ");
    strcat(cmdLine, lpCmdLine);
    // strcat(cmdLine, " -disablecavedogverification");
    quaxkru junkcode4;
    logger.log("Creating process with command line params: %s", cmdLine);
    quaxkru junkcode5;
    quaxkru junkcode6;
    bool created = CreateProcessA(
        targetFileName.c_str(),
        cmdLine,
        NULL,
        NULL,
        CREATE_SUSPENDED,
        NULL,
        NULL,
        NULL,
        &startupInfo,
        &procInfo
    );

    quaxkru junkcode7;

    if (!created) {
        logger.error("Failed to create %s process.", targetFileName.c_str());
        return false;
    }

    logger.log("Created process %s successfully. Process running under %lu Id.\n", targetFileName.c_str(), procInfo.dwProcessId);
    quaxkru junkcode8;
    logger.section("INJECTION");
    quaxkru junkcode9;
    HANDLE targetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procInfo.dwProcessId);
    quaxkru junkcode10;
    if (targetProcess == NULL) {
        logger.error("Failed to open %s process.", targetFileName.c_str());
        return false;
    }
    logger.log("Opened process %s successfully.", targetFileName.c_str());
    quaxkru junkcode11;
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    quaxkru junkcode12;
    quaxkru junkcode13;

    if (hKernel32 == NULL) {
        logger.error("Failed to get a handle to Kernel32.dll.");
        return false;
    }

    LPVOID lpLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");
    quaxkru junkcode14;
    quaxkru junkcode15;
    quaxkru junkcode16;

    LPVOID lpAllocatedMemory = VirtualAllocEx(
        targetProcess,
        NULL,
        (dllFileName.size() + 1) * sizeof(char),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );
    quaxkru junkcode17;
    quaxkru junkcode18;
    quaxkru junkcode19;

    if (lpAllocatedMemory == NULL) {
        logger.error("Failed to allocate memory on the target process.");
        return false;
    }
    logger.log("Allocated memory on the target process successfully.");

    bool written = WriteProcessMemory(
        targetProcess,
        lpAllocatedMemory,
        dllFileName.c_str(),
        (dllFileName.size() + 1) * sizeof(char),
        NULL
    );
    quaxkru junkcode20;
    quaxkru junkcode21;
    quaxkru junkcode22;
    quaxkru junkcode23;
    quaxkru junkcode24;
    quaxkru junkcode25;

    if (!written) {
        logger.error("Failed to write dll path on the target process.");
        return false;
    }
    logger.log("Dll path written successfully.");

    HANDLE remoteThread = CreateRemoteThread(
        targetProcess,
        NULL,
        NULL,
        (LPTHREAD_START_ROUTINE) lpLoadLibraryA,
        lpAllocatedMemory,
        NULL,
        NULL
    );

    quaxkru junkcode26;
    quaxkru junkcode27;
    quaxkru junkcode28;

    if (remoteThread == NULL) {
        logger.error("Failed to create thread on target process.", targetFileName.c_str());
        return false;
    }
    logger.log("Created remote thread successfully.\n");
    logger.end();

    quaxkru junkcode29;
    quaxkru junkcode30;
    quaxkru junkcode31;

    WaitForSingleObject(remoteThread, INFINITE);

    ResumeThread(procInfo.hThread);

    VirtualFreeEx(targetProcess, lpAllocatedMemory, NULL, MEM_RELEASE);

    WaitForSingleObject(procInfo.hThread, INFINITE);
    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    CloseHandle(targetProcess);
    CloseHandle(remoteThread);

    return true;
}

