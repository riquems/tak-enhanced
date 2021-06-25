#pragma once

#include "../../common.h"

class Window;

class BuildMenu
{
public:
	uintptr_t* vTable;        // 0x00
	char padding1[0x04];      // 0x04
	char padding2[0x04];      // 0x08
	char padding3[0x02];      // 0x12
	bool visible;             // 0x14
	char padding4[0x13];      // 0x15
	Window* parent;           // 0x28
	char padding5[0x04];
	uintptr_t* children;
};