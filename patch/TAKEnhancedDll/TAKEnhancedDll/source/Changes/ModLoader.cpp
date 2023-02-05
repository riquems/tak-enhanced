#include "TAKEnhancedDll/Changes/ModLoader.hpp"

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include <TAKEnhancedDll/Wrappers/Defs.h>
#include <TAKEnhancedDll/GlobalState.hpp>
#include <TAKCore/Models/HapiFile.h>

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

        logger->debug("Loading game file %s", hapiFile->filename);
        return true;
    }

    if (currentGameConfig->mods.enabled) {
        if (vector_has_str(currentGameConfig->mods.selectedMods, filename)) {
            hapiFile->allowed = true;
            hapiFile->allowed2 = true;

            logger->debug("Loading 3rd party file %s", hapiFile->filename);
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
