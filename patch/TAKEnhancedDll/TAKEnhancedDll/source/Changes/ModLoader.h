#pragma once

#include "../MemoryHandler.h"
#include "GlobalPointers/GlobalPointers.h"
#include "../GameFunctions.h"
#include "../Wrappers/Info.h"

extern "C" __declspec(dllexport) bool __stdcall HpiVerificationHook()
{
    HapiFile* hapiFile;

    __asm {
        mov hapiFile, esi
    }

    std::string filename(hapiFile->filename);

    if (vector_has_str(files_loaded_by_default, filename)) {
        hapiFile->allowed = true;
        hapiFile->allowed2 = true;
        return true;
    }

    if (settings.EnableMods) {
        if (vector_has_str(settings.SelectedMods, filename)) {
            hapiFile->allowed = true;
            hapiFile->allowed2 = true;

            return true;
        }
    }

    return false;
}

void applyModLoader()
{
    MemoryHandler::fillWithNOPs(Memory(0x08CD81, 0x08CD83));

    ShellCode shellcode("8BCE", Memory(0x08CD83, 0x08CD85)); // MOV ECX, ESI
    MemoryHandler::writeShellCode(shellcode);

    MemoryHandler::insertFunctionCall((DWORD) &HpiVerificationHook, 0x08CD85);
}
