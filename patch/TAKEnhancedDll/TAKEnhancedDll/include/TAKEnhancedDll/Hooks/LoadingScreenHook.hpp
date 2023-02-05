#pragma once
extern "C" __declspec(dllexport) bool firstLoad;

// replaces the call to this empty function: 004FABC0
// loading start
extern "C" __declspec(dllexport) void __stdcall LoadingScreenHook();

extern "C" __declspec(dllexport) void __stdcall LoadingScreenEndHook();

void applyLoadingScreenHooks();
