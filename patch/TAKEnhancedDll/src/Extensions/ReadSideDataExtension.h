#pragma once
#include "MemoryHandler.h"

extern "C" __declspec(dllexport) void __stdcall ReadSideDataExtension()
{
     int numberOfSides = 0;
    __asm {
        mov numberOfSides, ESI
    }

    DWORD* gamePtr = (DWORD*) (0x22D55C + baseAddress);
    *(int*)(*gamePtr + 0x3074) = numberOfSides;

    // numberOfSides++;
    /*DWORD side0Addr = *gamePtr + 0x3078;

    // Adding Random race
    
    DWORD randomSideAddr = side0Addr + (0xE0 * (numberOfSides - 1));

    std::string sideName("RANDOM");
    std::string sidePrefix("RAN");
    std::string sideCommander("RANDOM");

    memcpy((void*) randomSideAddr, sideName.c_str(), sideName.size() + 1);
    memcpy((void*) (randomSideAddr + 0x20), sidePrefix.c_str(), sidePrefix.size() + 1);
    memcpy((void*) (randomSideAddr + 0x24), sideCommander.c_str(), sideCommander.size() + 1); */
}

void applyReadSideDataExtensionPatch()
{
    MemoryHandling::fillWithNOPs(Memory(0x0C2E7B, 0x0C2E84));
    
    MemoryHandling::insertFunctionCall((DWORD) &ReadSideDataExtension, 0x0C2E7B);

    ShellCode shellCode(std::string("8D4DF4"), 0x0C2E81); // LEA ECX, [EBP-0C]
    MemoryHandling::writeShellCode(shellCode);

    logger.log("Added Read SideData.tdf Extension.");
}