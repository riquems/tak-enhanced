#include "TAKEnhancedDll/Wrappers/GameFunctions.h"

std::vector<HapiFile*> GameFunctionsExtensions::GetLoadedHapiFiles()
{
    std::vector<HapiFile*> hapiFiles;

    DWORD* filesPtr = (DWORD*)(GlobalPointers::ptr_241A48 + baseAddress);

    DWORD* hpiDirectory = (DWORD*)(*filesPtr + 0x5EA);
    DWORD* hpiFilesPtr = (DWORD*)(*hpiDirectory);
    HapiFile** hpiFiles = (HapiFile**)*hpiFilesPtr;

    HapiFile** nextHapiFile = hpiFiles;

    while (*nextHapiFile != nullptr && (*nextHapiFile)->vTable != 0) {
        hapiFiles.push_back(*nextHapiFile);
        std::cout << (*nextHapiFile)->filename << std::endl;
        nextHapiFile++;
    }

    return hapiFiles;
}
