#pragma once
#include "Utils/Windows.hpp"
#include <iostream>
#include <Utils/HelperFunctions.hpp>
#include <Utils/common.h>

void StartConsole(uint width = 600, uint height = 300, HWND zOrder = HWND_NOTOPMOST, bool borderless = false);
void CloseConsole();
void ConfigureConsole(uint width, uint height, HWND zOrder, bool borderless);
