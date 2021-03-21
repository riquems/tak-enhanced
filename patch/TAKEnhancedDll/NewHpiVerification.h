#pragma once

#include "MemoryHandler.h"
#include "GlobalPointers.h"
#include "GameFunctions.h"

extern "C" __declspec(dllexport) bool __stdcall HpiVerificationExtension()
{
	HapiFile* hapiFile;

	__asm {
		mov hapiFile, ecx
	}

	std::string std_filename(hapiFile->filename);

	if (vector_has_str(files_loaded_by_default, std_filename)) {
		hapiFile->allowed = true;
		hapiFile->allowed2 = true;
		return true;
	}

	if (settings.EnableMods) {
		if (vector_has_str(settings.selected_mods, std_filename)) {
			hapiFile->allowed = true;
			hapiFile->allowed2 = true;

			return true;
		}
	}

	return false;
}

void NewHpiVerificationPatch()
{
	ShellCode shellcode("8BCE", Memory(0x08CD83, 0x08CD85)); // MOV ECX, ESI
	MemoryHandling::writeShellCode(shellcode);

	MemoryHandling::insertFunctionCall((DWORD) &HpiVerificationExtension, 0x08CD85);
}