#pragma once
#include "../../common.h"

class Window;

class Gadget
{
public:
	uintptr_t* vTable;
	char padding[0x24];
	Window* parent;
};