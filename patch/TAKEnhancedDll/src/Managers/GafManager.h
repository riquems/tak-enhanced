#pragma once

#include "../Context.h"

#include "Models/UI/Window.h"
#include "Models/UI/Gadget.h"

#include "Functions/FunctionsOffsets.h"

#include <iostream>

class GafManager
{
public:
	GafManager() {}

	std::shared_ptr<Window*> getWindow(const char* name);
	std::shared_ptr<Gadget*> getGadget(std::shared_ptr<Window*> window, const char* name);
};

std::shared_ptr<Window*> GafManager::getWindow(const char* name)
{
	uintptr_t (__stdcall *getWindow)(const char*, int) = (uintptr_t (__stdcall *)(const char*, int)) (FunctionsOffsets::getWindow + baseAddress);
	uintptr_t windowAddr = getWindow(name, 0);

	//std::cout << "Addr: " << std::hex << windowAddr << std::endl;

	if (windowAddr == 0)
		return nullptr;

	Window* windowPtr = (Window*) windowAddr;

	/*std::cout << "Addr Ptr is Point to: " << std::hex << *(uintptr_t*) windowPtr << std::endl;

	return nullptr;*/

	std::shared_ptr<Window*> window = std::make_shared<Window*>(windowPtr);
	return window;
}

std::shared_ptr<Gadget*> GafManager::getGadget(std::shared_ptr<Window*> window, const char* name)
{
	uintptr_t windowAddr = *(uintptr_t*) window.get();

	__asm {
		PUSH ECX
		MOV  ECX, windowAddr
	}

	uintptr_t (__stdcall *getGadget)(const char*, int) = (uintptr_t (__stdcall *)(const char*, int)) (FunctionsOffsets::getGadget + baseAddress);
	uintptr_t gadgetAddr = getGadget(name, 0);

	__asm {
		POP ECX
	}

	if (gadgetAddr == 0)
		return nullptr;

	Gadget* gadgetPtr = (Gadget*) gadgetAddr;
	std::shared_ptr<Gadget*> gadget = std::make_shared<Gadget*>(gadgetPtr);
	return gadget;
}