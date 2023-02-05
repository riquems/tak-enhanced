#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Utils/Logger.h"
#include "Utils/JunkCode.h"
#include <Utils/json.hpp>
#include "AppConfig.hpp"
#include <Utils/Console.hpp>

//int make_TAK_inject_ETAK()
//{
//    std::fstream takexe(targetFileName);
//
//    if (takexe.is_open()) {
//        takexe.seekp(0x2271C5);
//
//        takexe.write("TAKEnhanced", 12);
//
//        takexe.seekp(0x227264);
//
//        takexe.write("TAKEnhanced", 12);
//    }
//    else {
//        takexe.close();
//        return -1;
//    }
//
//    takexe.close();
//    return 1;
//}

int EnableCommandLineParams(std::string target)
{
    std::fstream takexe(target);

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

using json = nlohmann::json;

BOOL WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    StartConsole();

    std::string fileName = "Kingdoms.cfg.json";
    std::fstream fileStream(fileName);

    if (!fileStream.is_open()) {
        std::cout << "Couldn't open file " << fileName << "\n";
    }

    json json;
    fileStream >> json;
    
    auto config = json.get<AppConfig>();

    Logger logger(config.logger, "w");

    bool dllExists = std::filesystem::exists(config.dll);

    if (!dllExists) {
        logger.error("Couldn't find DLL %s", config.dll);
        return false;
    }

    bool targetExists = std::filesystem::exists(config.target);

    if (!targetExists) {
        logger.error("Couldn't find target %s", config.target);
        return false;
    }

    std::string dllFileName(config.dll);
    std::string targetFileName(config.target);

    logger.context("EXE");

    quaxkru junkcode;
    STARTUPINFOA startupInfo = {};
    PROCESS_INFORMATION procInfo;

    logger.section("PREPARATION");

    quaxkru junkcode2;
    int status = EnableCommandLineParams(config.target);

    if (status == -1) {
        auto errorCode = GetLastError();

        if (errorCode == 32) {
            logger.error("Couldn't open target file %s. It looks like your game is running, try closing it or shutting it down using the Task Manager.", targetFileName.c_str());
            return false;
        }

        logger.fatal("Couldn't open target file %s.", targetFileName.c_str());
        return false;
    }
    else if (status == 0) {
        logger.debug("Command line params are already enabled.");
    }
    else {
        logger.debug("Command line params enabled.");
    }

    quaxkru junkcode3;

    char cmdLine[256];

    strcpy(cmdLine, targetFileName.c_str());
    strcat(cmdLine, " ");
    strcat(cmdLine, lpCmdLine);
    strcat(cmdLine, " -disablecavedogverification");
    quaxkru junkcode4;
    logger.info("Creating process with command line params: %s", cmdLine);
    quaxkru junkcode5;
    quaxkru junkcode6;
    bool created = CreateProcessA(
        targetFileName.c_str(),
        cmdLine,
        NULL,
        NULL,
        FALSE,
        CREATE_SUSPENDED,
        NULL,
        NULL,
        &startupInfo,
        &procInfo
    );
    quaxkru junkcode7;

    if (!created) {
        logger.fatal("Failed to create %s process.", targetFileName.c_str());
        return false;
    }

    logger.info("Created process %s successfully. Process running under %lu Id.", targetFileName.c_str(), procInfo.dwProcessId);
    quaxkru junkcode8;
    logger.section("INJECTION");
    quaxkru junkcode11;
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    quaxkru junkcode12;
    quaxkru junkcode13;

    if (hKernel32 == NULL) {
        logger.fatal("Failed to get a handle to Kernel32.dll.");
        return false;
    }

    LPVOID lpLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");
    quaxkru junkcode14;
    quaxkru junkcode15;
    quaxkru junkcode16;

    LPVOID lpAllocatedMemory = VirtualAllocEx(
        procInfo.hProcess,
        NULL,
        (dllFileName.size() + 1) * sizeof(char),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );
    quaxkru junkcode17;
    quaxkru junkcode18;
    quaxkru junkcode19;

    if (lpAllocatedMemory == NULL) {
        logger.fatal("Failed to allocate memory on the target process.");
        return false;
    }
    logger.info("Allocated memory on the target process successfully.");

    bool written = WriteProcessMemory(
        procInfo.hProcess,
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
    logger.info("Dll path written successfully.");

    HANDLE remoteThread = CreateRemoteThread(
        procInfo.hProcess,
        NULL,
        NULL,
        (LPTHREAD_START_ROUTINE) lpLoadLibraryA,
        lpAllocatedMemory,
        CREATE_SUSPENDED,
        NULL
    );

    quaxkru junkcode26;
    quaxkru junkcode27;
    quaxkru junkcode28;

    if (remoteThread == NULL) {
        logger.error("Failed to create thread on target process.", targetFileName.c_str());
        return false;
    }
    logger.info("Created remote thread successfully.\n");
    
    logger.stop();
    if (config.debugMode) {
        std::cout << "Press any key to continue...\n";
        std::cin.get();
    }

    CloseConsole();

    quaxkru junkcode29;
    quaxkru junkcode30;
    quaxkru junkcode31;

    ResumeThread(remoteThread);
    WaitForSingleObject(remoteThread, INFINITE);
    VirtualFreeEx(procInfo.hProcess, lpAllocatedMemory, NULL, MEM_RELEASE);

    /*Logger disposeLogger(config.logger, "a");
    disposeLogger.context("EXE");
    disposeLogger.info("Resuming main thread...");
    disposeLogger.stop();*/
    
    ResumeThread(procInfo.hThread);
    WaitForSingleObject(procInfo.hThread, INFINITE);

    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    CloseHandle(remoteThread);

    return true;
}
