#pragma once

#include "MemoryHandler.h"
#include "GlobalPointers.h"
#include "GameFunctions.h"
#include "../Wrappers/Info.h"

extern "C" __declspec(dllexport) bool __stdcall HpiVerificationExtension()
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
		if (vector_has_str(settings.selected_mods, filename)) {
			hapiFile->allowed = true;
			hapiFile->allowed2 = true;

			return true;
		}
	}

	return false;
}

void applyNewHpiVerificationPatch()
{
	ShellCode shellcode("8BCE", Memory(0x08CD83, 0x08CD85)); // MOV ECX, ESI
	MemoryHandling::writeShellCode(shellcode);

	MemoryHandling::insertFunctionCall((DWORD) &HpiVerificationExtension, 0x08CD85);
}