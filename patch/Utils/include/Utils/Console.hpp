#pragma once
#include "Utils/Windows.hpp"
#include <iostream>
#include <Utils/HelperFunctions.hpp>
#include <Utils/common.h>

void StartConsole();
void CloseConsole();
void ConfigureConsole(uint width, uint height, HWND zOrder, bool borderless);
