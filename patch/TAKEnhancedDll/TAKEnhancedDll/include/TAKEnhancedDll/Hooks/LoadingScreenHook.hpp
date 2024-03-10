#pragma once
extern "C" __declspec(dllexport) bool inLoadingScreen;

// replaces the call to this empty function: 004FABC0
// loading start
extern "C" __declspec(dllexport) void __stdcall LoadingScreenStartHook();

extern "C" __declspec(dllexport) void __stdcall LoadingScreenEndHook();

void applyLoadingScreenHooks();
