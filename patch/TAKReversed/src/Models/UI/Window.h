#pragma once
#include "../../common.h"

class Gadget;

class Window
{
public:
	uintptr_t* vTable;
	char padding[44];
	Gadget* children;
};
