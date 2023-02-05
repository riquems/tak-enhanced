#pragma once
#include <Utils/Windows.hpp>
#include <string>

extern "C" bool isFullscreen;

HWND GetThisWindow(std::string name);
void ToggleFullscreen();
