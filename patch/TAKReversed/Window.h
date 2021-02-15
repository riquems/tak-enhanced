#pragma once
#include "common.h"

class Gadget;

class Window
{
public:
	DWORD* vTable;
	char padding[44];
	Gadget* children;
};
