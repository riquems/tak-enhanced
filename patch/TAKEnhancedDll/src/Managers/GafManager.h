#pragma once

#include "../Context.h"

#include "Models/UI/Window.h"
#include "Models/UI/Gadget.h"

#include "Functions/FunctionsOffsets.h"

class GafManager
{
public:
	GafManager() {}

	Window* getWindow(const char* name);
	Gadget* getGadget(Window* window, const char* name);
};

Window* GafManager::getWindow(const char* name)
{
	uintptr_t (__stdcall *getWindow)(const char*, int) = (uintptr_t  (__stdcall *)(const char*, int)) (FunctionsOffsets::getWindow + baseAddress);

	Window* window = (Window*) getWindow(name, 0);
	return window;
}

Gadget* GafManager::getGadget(Window* window, const char* name)
{
	uintptr_t windowAddr = *(uintptr_t*) window;

	__asm {
		PUSH ECX
		MOV  ECX, windowAddr
	}

	uintptr_t (__stdcall *getGadget)(const char*, int) = (uintptr_t (__stdcall *)(const char*, int)) (FunctionsOffsets::getGadget + baseAddress);
	Gadget* gadget = (Gadget*) getGadget(name, 0);

	__asm {
		POP ECX
	}

	return gadget;
}