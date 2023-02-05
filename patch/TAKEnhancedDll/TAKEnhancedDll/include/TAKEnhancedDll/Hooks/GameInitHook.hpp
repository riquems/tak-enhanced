#pragma once

void installGameInitHook();

extern "C" __declspec(dllexport) void __stdcall GameInitHook();
