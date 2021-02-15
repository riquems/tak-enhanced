#pragma once
#include "common.h"

class Window;

class Gadget
{
public:
	DWORD* vTable;
	char padding[0x24];
	Window* parent;
};