#pragma once
#include "../../common.h"

class Gadget;

class Window
{
public:                       // offset
	uintptr_t* vTable;        // 0x00
	char padding1[0x20];      // 0x04
	const char* name;         // 0x24
	char padding2[0x04];      // 0x28
	char padding3[0x04];      // 0x2C
	Gadget* children;         // 0x30
};
