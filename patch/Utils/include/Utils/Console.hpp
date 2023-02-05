#pragma once
#pragma pack(push, 8)
#include <Windows.h>
#pragma pack(pop)
#include <iostream>
#include <Utils/HelperFunctions.hpp>
#include <Utils/common.h>

void StartConsole();
void CloseConsole();
void ConfigureConsole(uint width, uint height, HWND zOrder, bool borderless);
